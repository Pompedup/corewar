/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_elem.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 15:34:54 by abezanni          #+#    #+#             */
/*   Updated: 2018/10/15 17:32:46 by abezanni         ###   ########.fr       */
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
	char	**split;
	t_elem	*to_free;

	to_free = *current;
	split = (*current)->split;
	while (*split)
		free(*(split++));
	free((*current)->split);
	del_t_args(&to_free->args);
	*current = (*current)->next;
	free(to_free);
}

void	del_t_elems(t_elem **current)
{
	while (*current)
		del_t_elem(current);
}

t_bool	new_t_elem(t_record *record, t_elem **current, int type)
{
	if (!(*current = ft_memalloc(sizeof(t_elem))))
	{
		ft_printf(ALLOC,
			record->file_name);
		return (FALSE);
	}
	(*current)->op_case = g_op_tab[type];
	(*current)->type = type;
	(*current)->complete = TRUE;
	(*current)->addr = record->tot;
	(*current)->size = 1;
	return (TRUE);
}
