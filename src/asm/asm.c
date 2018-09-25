/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 12:23:45 by abezanni          #+#    #+#             */
/*   Updated: 2018/09/25 17:27:07 by abezanni         ###   ########.fr       */
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
		init(&record, av[i]);
		get_infos(&record, &record.file);
		if (!record.name || !record.comment)
			exit(0);
		name_and_comment(record);//affichage
		get_function(&record, &record.file, &(record.functions));
		i++;
		print_functions(record.functions);
		erase(&record);
	}
	//print_lines(record.lines);
	//verification fichier
	//creation data pour le .cor
	//creation du .cor
	return (0);
}
