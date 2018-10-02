/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_verifications.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/26 17:56:26 by abezanni          #+#    #+#             */
/*   Updated: 2018/10/02 17:19:45 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	get_addr(t_record *record, t_function *functions, t_arg *arg)
{
	while (functions)
	{
		if (!ft_strcmp(functions->name, arg->copy))
		{
			arg->value = functions->addr - arg->addr;
			arg->handled = TRUE;
			return ;
		}
		functions = functions->next;
	}
	ft_putendl(arg->copy);
	(void)record;
	exit(0); //gerer l'erreur
}

void	handle_elem(t_record *record, t_elem *elem)
{
	t_arg *args;

	args = elem->args;
	while (args)
	{
		if (!args->handled)
			get_addr(record, record->functions, args);
		args = args->next;
	}
	elem->complete = TRUE;
}

t_bool	last_verifications(t_record *record)
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
				handle_elem(record, elems);
			elems = elems->next;
		}
		functions = functions->next;
	}
	return (TRUE);
}
