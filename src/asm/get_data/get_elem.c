/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_elem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 14:27:56 by abezanni          #+#    #+#             */
/*   Updated: 2018/10/30 18:39:45 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
********************************************************************************
********************************************************************************
*/

static t_bool	get_value_arg(t_record *record, t_elem *elem, t_arg *arg, int i)
{
	if (arg->type == 1)
	{
		if (!get_reg(record, elem, arg, i))
			return (FALSE);
	}
	else if (arg->type == 2)
	{
		if (!get_dir(record, elem, arg, i))
			return (FALSE);
	}
	else if (arg->type == 4)
	{
		if (!get_ind(record, elem, arg, i))
			return (FALSE);
	}
	return (TRUE);
}

/*
********************************************************************************
********************************************************************************
*/

t_bool			get_elem(t_record *record, t_elem *elem)
{
	int		i;
	t_arg	**arg;

	if (!verify_elem_str(record, elem))
		return (FALSE);
	i = 0;
	arg = &(elem->args);
	while (i < elem->op_case.arg_authorized && *elem->line)
	{
		if (!(get_value_arg(record, elem, *arg, i)))
			return (FALSE);
		arg = &(*arg)->next;
		i++;
	}
	if (elem->op_case.arg_authorized > 1 || elem->op_case.id == 16)
		elem->size++;
	return (TRUE);
}
