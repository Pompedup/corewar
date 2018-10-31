/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 15:10:17 by abezanni          #+#    #+#             */
/*   Updated: 2018/10/31 17:12:56 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_bool	write_arg(t_record *record, t_arg *arg, int fd)
{
	ft_memrev(&arg->value, arg->size);
	if (write(fd, &arg->value, arg->size) == -1)
	{
		ft_printf(WRITEER, record->final_name);
		return (FALSE);
	}
	return (TRUE);
}

t_bool	write_key(t_record *record, t_elem *elem, int fd)
{
	t_arg *args;

	if (write(fd, &g_op_tab[elem->type].id, 1) == -1)
	{
		ft_printf(WRITEER, record->final_name);
		return (FALSE);
	}
	if (elem->op_case.nbr_arg > 1 || elem->op_case.id == 16)
	{
		if (write(fd, &elem->key, 1) == -1)
		{
			ft_printf(WRITEER, record->final_name);
			return (FALSE);
		}
	}
	args = elem->args;
	while (args)
	{
		if (!(write_arg(record, args, fd)))
			return (FALSE);
		args = args->next;
	}
	return (TRUE);
}

t_bool	print_four(t_record *record, int fd, int nb)
{
	unsigned char	magic[4];
	int				i;

	i = 0;
	while (i < 4)
	{
		magic[i] = (nb >> (24 - (8 * i))) & 255;
		i++;
	}
	if (write(fd, magic, 4) == -1)
	{
		ft_printf(WRITEER, record->final_name);
		return (FALSE);
	}
	return (TRUE);
}

t_bool	print_description(t_record *record, int fd)
{
	if (!print_four(record, fd, COREWAR_EXEC_MAGIC))
		return (FALSE);
	if (write(fd, record->name, PROG_NAME_LENGTH) == -1)
	{
		ft_printf(WRITEER, record->final_name);
		return (FALSE);
	}
	if (!print_four(record, fd, 0))
		return (FALSE);
	if (!print_four(record, fd, record->tot))
		return (FALSE);
	if (write(fd, record->comment, COMMENT_LENGTH) == -1)
	{
		ft_printf(WRITEER, record->final_name);
		return (FALSE);
	}
	if (!print_four(record, fd, 0))
		return (FALSE);
	return (TRUE);
}

void	write_file(t_record *record, t_function *functions)
{
	t_elem	*elems;
	int		fd;

	if ((fd = open(record->final_name, O_TRUNC | O_WRONLY | O_CREAT, 0666))\
		== -1)
	{
		ft_printf(OPENNEW, record->file_name, record->final_name);
		return ;
	}
	if (!print_description(record, fd))
		return ;
	while (functions)
	{
		elems = functions->elems;
		while (elems)
		{
			if (!write_key(record, elems, fd))
				return ;
			elems = elems->next;
		}
		functions = functions->next;
	}
	close(fd);
	ft_printf(GWR, record->file_name, record->final_name);
}
