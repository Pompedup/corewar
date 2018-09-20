/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 12:23:45 by abezanni          #+#    #+#             */
/*   Updated: 2018/09/20 16:38:04 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*void		error(int ret, char *name)
{
	ft_putendl(name);
	ft_putnbrendl(ret);
}*/

void		print_lines(t_lines *lines)
{
	while (lines)
	{
		ft_putendl(lines->str);
		lines = lines->next;
	}
}

void		name_and_comment(t_record record)
{
	ft_putendl(record.name);
	ft_putendl(record.comment);
}

int			main(int ac, char **av)
{
	t_record	record;
	int			i;
	int			ret;

	if (ac < 2)
		ft_putendl("usage: ./data/asm [-a] <sourcefile.s>\n\t-a : Instead of \
		creating a .cor file, outputs a stripped and annotated version of the \
		code to the standard output");
	i = 1;
	while (i < ac)
	{
		init(&record, av[i]);
		if ((ret = get_lines(av[i], &(record.lines))))
			error(&record, ret);
		get_infos(&record);
		name_and_comment(record);//affichage
		get_functions(&record, &(record.lines), &(record.functions));
		i++;
		erase(&record);
	}
	record.lines = NULL;
	//print_lines(record.lines);
	//verification fichier
	//creation data pour le .cor
	//creation du .cor
	return (0);
}
