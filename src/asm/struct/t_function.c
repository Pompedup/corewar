/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_function.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 15:43:02 by abezanni          #+#    #+#             */
/*   Updated: 2018/09/28 16:54:34 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	print_functions(t_function *current)
{
	while (current)
	{
		ft_printf("\033[0;31mFunctions\033[0;0m\nName : %s\nAddr %x\n",\
			current->name, current->addr);
		print_elems(current->elems);
		current = current->next;
	}
}

void	del_t_function(t_function **current)
{
	t_function *to_free;

	to_free = *current;
	del_t_elems(&(to_free->elems));
	*current = (*current)->next;
	free(to_free);
}

void	del_t_functions(t_function **current)
{
	while (*current)
		del_t_function(current);
}

void	new_t_function(t_function **current, char *name, int addr)
{
	if (!(*current = ft_memalloc(sizeof(t_function))))
		return ;//cas derreur a gerer
	(*current)->name = name;
	(*current)->addr = addr;
}
