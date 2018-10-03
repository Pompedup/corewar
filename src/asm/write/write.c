/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 15:10:17 by abezanni          #+#    #+#             */
/*   Updated: 2018/10/03 17:06:42 by abezanni         ###   ########.fr       */
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

void	print_four(int fd, int nb)
{
	unsigned char	magic[4];
	int		i;

	i = 0;
	while (i < 4)
	{
		magic[i] = (nb >> (24 - (8 * i))) & 255;
		i++;
	}
	write(fd, magic, 4);
}
//00ea 83f3
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
	print_four(fd, COREWAR_EXEC_MAGIC);
	write(fd, record->name, PROG_NAME_LENGTH);
	print_four(fd, 0);
	print_four(fd, record->tot);
	write(fd, record->comment, COMMENT_LENGTH);
	print_four(fd, 0);
	while (functions)
	{
		elems = functions->elems;
		while (elems)
		{
			write_key(elems, fd);
			elems = elems->next;
		}
		functions = functions->next;
	}
	close(fd);
}
