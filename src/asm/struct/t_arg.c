/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_arg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 17:37:50 by pompedup          #+#    #+#             */
/*   Updated: 2018/10/20 19:18:33 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	print_args(t_arg *current)
{
	while (current)
	{
		ft_printf("%8s\033[s\v\b\b\b\b\b\b\b\b%8d\033[u\t\t", current->copy,\
			current->value);
		current = current->next;
	}
}

void	del_t_arg(t_arg **current)
{
	t_arg *to_free;

	to_free = *current;
	*current = (*current)->next;
	free(to_free);
}

void	del_t_args(t_arg **current)
{
	while (*current)
		del_t_arg(current);
}

void	new_t_arg(t_arg **current, int addr, char *copy)
{
	if (!(*current = ft_memalloc(sizeof(t_arg))))
		return ;
	(*current)->addr = addr;
	(*current)->str = copy;
	(*current)->copy = copy;
}
