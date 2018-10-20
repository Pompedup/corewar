/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 21:45:22 by abezanni          #+#    #+#             */
/*   Updated: 2018/10/20 21:45:56 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static t_bool	write_good_type(int nb_type, t_bool two)
{
	char	*type;

	if (nb_type != 1)
		type = nb_type == 2 ? "DIR" : "IND";
	else
		type = "REG";
	ft_printf("%s %s", two ? " or" : "", type);
	return (TRUE);
}

t_bool			error_type(t_record *record, t_elem *elem, t_arg *arg, int i)
{
	char	*pos;
	char	*type;
	int		j;
	t_bool	two;

	if (i)
		pos = i == 1 ? "second" : "third";
	else
		pos = "first";
	if (arg->type != 1)
		type = arg->type == 2 ? "DIR" : "IND";
	else
		type = "REG";
	ft_printf(WRTYPE, record->file_name, elem->index_line, type,\
		elem->op_case.shortcut, pos);
	j = 1;
	two = FALSE;
	while (j < 5)
	{
		if (j & elem->op_case.accept[i])
			two = write_good_type(j, two);
		j *= 2;
	}
	ft_printf(".\n");
	return (FALSE);
}
