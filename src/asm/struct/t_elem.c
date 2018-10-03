/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_elem.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 15:34:54 by abezanni          #+#    #+#             */
/*   Updated: 2018/10/03 18:15:49 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	print_elems(t_elem *current)
{
	while (current)
	{
		ft_printf("\033[0;32mElems\033[0;0m\nAddr : %x\nType %d\nKey : %x\nHandled %s\n",\
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
	free(to_free);
}

void	del_t_elems(t_elem **current)
{
	while (*current)
		del_t_elem(current);
}

t_bool	new_t_elem(t_record *record, t_elem **current, int type, int addr)
{
	if (!(*current = ft_memalloc(sizeof(t_elem))))
	{
		ft_printf("Allocation in new_t_elem didn't work for : %s\n",
			record->name_file);
		return (FALSE);
	}
	(*current)->type = type;
	(*current)->complete = TRUE;
	(*current)->addr = addr;
	(*current)->size = 1;
	return (TRUE);
}
