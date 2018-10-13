/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_function.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 15:43:02 by abezanni          #+#    #+#             */
/*   Updated: 2018/10/13 16:53:18 by abezanni         ###   ########.fr       */
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

t_bool	new_t_function(t_record *record, t_function **current,\
					char *name)
{
	if (!(*current = ft_memalloc(sizeof(t_function))))
	{
		ft_printf("Allocation in new_t_function didn't work for : %s\n",
			record->file_name);
		return (FALSE);//cas derreur a gerer
	}
	(*current)->name = name;
	(*current)->addr = record->tot;
	return (TRUE);
}
