/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 15:10:17 by abezanni          #+#    #+#             */
/*   Updated: 2018/09/28 17:30:35 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

extern t_op	g_op_tab[];

void	write_arg(t_arg *arg, int fd)
{
	ft_memrev(&arg->value, arg->size);
	write(fd, &arg->value, arg->size);
}

void	write_key(t_elem *elem, int fd)
{
	t_arg *args;


	write(fd, &g_op_tab[elem->type].id, 1);
	if (elem->key)
		write(fd, &elem->key, 1);
	args = elem->args;
	while (args)
	{
		write_arg(args, fd);
		args = args->next;
	}
}

void	write_file(t_record *record, t_function *functions)
{
	t_elem	*elems;
	int		fd;

	record->name_file = "asm_de_moi";
	if ((fd = open(record->name_file, O_TRUNC|O_WRONLY|O_CREAT, 0666)) == -1)
	{
		ft_putendl("naaaan");
		exit(0); //gerer l'erreur
	}
	char *test;
	test = ft_memalloc(2192);
	if (write(fd, test, 2192) == -1)
		ft_putendl("that's why");
	free(test);
	while (functions)
	{
		elems = functions->elems;
		while (elems)
		{
			write_key(elems, fd);
			if (!elems->next)
				ft_printf("%d\n", elems->addr);
			elems = elems->next;
		}
		functions = functions->next;
	}
	close(fd);
}
