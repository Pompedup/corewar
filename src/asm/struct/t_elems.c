/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_elems.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 15:34:54 by abezanni          #+#    #+#             */
/*   Updated: 2018/09/03 18:42:27 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	del_t_elem(t_elems **current)
{
	t_elems *to_free;

	to_free = *current;
	*current = (*current)->next;
}

void	del_t_elems(t_elems **current)
{
	while (*current)
		del_t_elem(current);
}

void	new_t_elem(t_elems **current, int type, int key)
{
	if (*current)
		*current = (*current)->next;
	if (!(*current = malloc(sizeof(t_elems))))
		return ;
	bzero(*current, sizeof(t_elems));
	(*current)->type = type;
	(*current)->key = key;
}
