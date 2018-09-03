/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_lines.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 17:37:50 by pompedup          #+#    #+#             */
/*   Updated: 2018/09/03 21:43:37 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	del_t_line(t_lines **current)
{
	t_lines *to_free;

	to_free = *current;
	*current = (*current)->next;
	free(to_free->str);
	free(to_free);
}

void	del_t_lines(t_lines **current)
{
	while (*current)
		del_t_line(current);
}

void	new_t_line(t_lines **current, char *line, int num)
{
	if (!(*current = malloc(sizeof(t_lines))))
		return ;
	(*current)->str = line;
	(*current)->num_line = num;
	(*current)->next = NULL;
}
