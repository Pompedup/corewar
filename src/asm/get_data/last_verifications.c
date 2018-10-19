/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_verifications.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/26 17:56:26 by abezanni          #+#    #+#             */
/*   Updated: 2018/10/18 15:32:31 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static t_bool	get_addr(t_record *record, t_function *functions, t_arg *arg)
{
	while (functions)
	{
		if (!ft_strcmp(functions->name, arg->copy + 1))
		{
			arg->value = functions->addr - arg->addr;
			arg->handled = TRUE;
			return (TRUE);
		}
		functions = functions->next;
	}
	//elem->index_line contient le numero de la line
	ft_printf("\033[0;34m%s\033[0m : Unknow label [\033[0;31m%s\033[0m]\n",
		record->file_name, arg->copy + 1);
	return (FALSE);
}

static t_bool	handle_elem(t_record *record, t_elem *elem)
{
	t_arg *args;

	args = elem->args;
	while (args)
	{
		if (!args->handled)
			if (!(get_addr(record, record->functions, args)))
				return (FALSE);
		args = args->next;
	}
	elem->complete = TRUE;
	return (TRUE);
}

t_bool			last_verifications(t_record *record)
{
	t_function	*functions;
	t_elem		*elems;

	functions = record->functions;
	while (functions)
	{
		elems = functions->elems;
		while (elems)
		{
			if (!elems->complete)
				if (!(handle_elem(record, elems)))
					return (FALSE);
			elems = elems->next;
		}
		functions = functions->next;
	}
	return (TRUE);
}