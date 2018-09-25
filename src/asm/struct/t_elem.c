/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_elem.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 15:34:54 by abezanni          #+#    #+#             */
/*   Updated: 2018/09/25 17:25:06 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	print_elems(t_elem *current)
{
	while (current)
	{
		ft_printf("\033[0;32mElems\033[0;0m\nAddr : %d\nType %d\nKey : %d\nHandled %s\n",\
			current->addr, current->type, current->key, current->complete ? "True" : "False");
		print_args(current->args);
		current = current->next;
	}
}

void	del_t_elem(t_elem **current)
{
	t_elem *to_free;

	to_free = *current;
	del_t_args(&to_free->args);
	*current = (*current)->next;
}

void	del_t_elems(t_elem **current)
{
	while (*current)
		del_t_elem(current);
}

void	new_t_elem(t_elem **current, int type, int addr)
{
	if (!(*current = ft_memalloc(sizeof(t_elem))))
		return ;
	(*current)->type = type;
	(*current)->addr = addr;
}
