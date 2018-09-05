/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_functions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 15:43:02 by abezanni          #+#    #+#             */
/*   Updated: 2018/09/05 15:39:21 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	del_t_function(t_functions **current)
{
	t_functions *to_free;

	to_free = *current;
	*current = (*current)->next;
}

void	del_t_functions(t_functions **current)
{
	while (*current)
		del_t_function(current);
}

t_functions	**new_t_function(t_functions **current, char *name, int pos)
{
	if (*current)
		current = &((*current)->next);
	if (!(*current = malloc(sizeof(t_functions))))
		return (NULL);
	bzero(*current, sizeof(t_functions));
	(*current)->name = name;
	(*current)->pos = pos;
	return (current);
}