/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 12:23:45 by abezanni          #+#    #+#             */
/*   Updated: 2018/10/04 15:31:23 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*void		error(int ret, char *name)
{
	ft_putendl(name);
	ft_putnbrendl(ret);
}*/

void		name_and_comment(t_record record)
{
	ft_putendl("in name and comment");
	ft_putendl(record.name);
	ft_putendl(record.comment);
	ft_putendl("out name and comment");
}

int			main(int ac, char **av)
{
	t_record	record;
	int			i;
	//int			ret;

	if (ac < 2)
		ft_putendl("usage: ./data/asm [-a] <sourcefile.s>\n\t-a : Instead of \
		creating a .cor file, outputs a stripped and annotated version of the \
		code to the standard output");
	i = 1;
	while (i < ac)
	{
		//while (verif_name(ac[i]) && i < ac)
		//	i++;
		if (i == ac)
			return (0);
		init(&record, av[i]);
		if (get_infos(&record, &record.file))
		{
			if (!record.name_complete || !record.comment_complete)
				ft_putendl("Manque le nom ou le comment");
			else
			{
				// name_and_comment(record);//affichage
				// ft_putendl("function");
				if (get_function(&record, &record.file, &(record.functions)))
				{
					// ft_putendl("last");
					if (last_verifications(&record))
					{
						// ft_putendl("write");
						write_file(&record, record.functions);
					}
				}
			}
		}
		i++;
		//print_functions(record.functions);
		erase(&record);
	}
	//print_lines(record.lines);
	//verification fichier
	//creation data pour le .cor
	//creation du .cor
	return (0);
}

//label
//instruction
//.comment .name
