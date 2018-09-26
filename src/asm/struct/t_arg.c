/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_arg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 17:37:50 by pompedup          #+#    #+#             */
/*   Updated: 2018/09/26 17:33:51 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	print_args(t_arg *current)
{
	while (current)
	{
		ft_printf("\033[0;34mArg\033[0;0m\nType : %d\nValue %x\nHandled %s\n", current->type,\
			current->value, current->handled ? "True" : "False");
		current = current->next;
	}
}

void	del_t_arg(t_arg **current)
{
	t_arg *to_free;

	to_free = *current;
	*current = (*current)->next;
	//free(to_free->str);
	free(to_free);
}

void	del_t_args(t_arg **current)
{
	while (*current)
		del_t_arg(current);
}

void	new_t_arg(t_arg **current, int addr)
{
	if (!(*current = ft_memalloc(sizeof(t_arg))))
		return ;
	(*current)->addr = addr;
}
