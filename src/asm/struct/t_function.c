/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_function.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 15:43:02 by abezanni          #+#    #+#             */
/*   Updated: 2018/10/31 18:21:37 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
********************************************************************************
********************************************************************************
*/

void	print_functions(t_function *current)
{
	while (current)
	{
		if (current->name)
			ft_printf(FUNC, current->name, current->addr);
		print_elems(current->elems);
		current = current->next;
	}
}

/*
********************************************************************************
********************************************************************************
*/

void	del_t_function(t_function **current)
{
	t_function *to_free;

	to_free = *current;
	free((*current)->name);
	del_t_elems(&(to_free->elems));
	*current = (*current)->next;
	free(to_free);
}

/*
********************************************************************************
********************************************************************************
*/

void	del_t_functions(t_function **current)
{
	while (*current)
		del_t_function(current);
}

/*
********************************************************************************
********************************************************************************
*/

t_bool	new_t_function(t_record *record, t_function **current,\
					char *name)
{
	if (!(*current = ft_memalloc(sizeof(t_function))))
	{
		ft_printf(ALLOC, record->file_name);
		erase(record);
		exit(0);
	}
	(*current)->name = name;
	(*current)->addr = record->tot;
	return (TRUE);
}
