/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_elem.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecesari <ecesari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 15:34:54 by abezanni          #+#    #+#             */
/*   Updated: 2018/11/01 15:28:02 by ecesari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
********************************************************************************
********************************************************************************
*/

void	print_elems(t_elem *current)
{
	if (current)
		ft_printf("Address\t\tSize\t\tType\t\tArg1\t\tArg2\t\tArg3\n");
	while (current)
	{
		ft_printf("%8d\t%8d\t%8s",\
			current->addr, current->size, g_op_tab[current->type].shortcut);
		print_args(current->args);
		ft_printf("\n\n");
		current = current->next;
	}
}

/*
********************************************************************************
********************************************************************************
*/

void	del_t_elem(t_elem **current)
{
	char	**split;
	t_elem	*to_free;

	to_free = *current;
	split = (*current)->split;
	while (split && *split)
		free(*(split++));
	free((*current)->split);
	del_t_args(&to_free->args);
	*current = (*current)->next;
	free(to_free);
}

/*
********************************************************************************
********************************************************************************
*/

void	del_t_elems(t_elem **current)
{
	while (*current)
		del_t_elem(current);
}

/*
********************************************************************************
********************************************************************************
*/

t_bool	new_t_elem(t_record *record, t_elem **current, int type)
{
	if (!(*current = ft_memalloc(sizeof(t_elem))))
	{
		ft_printf(ALLOC, record->file_name);
		erase(record);
		exit(0);
	}
	(*current)->op_case = g_op_tab[type];
	(*current)->type = type;
	(*current)->complete = TRUE;
	(*current)->addr = record->tot;
	(*current)->size = 1;
	return (TRUE);
}
