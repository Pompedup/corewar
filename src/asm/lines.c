/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pompedup <pompedup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 17:37:50 by pompedup          #+#    #+#             */
/*   Updated: 2018/09/01 17:39:34 by pompedup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	delete_t_lines(t_lines **lines)
{
	t_lines *to_free;

	to_free = *lines;
	lines = &((*lines)->next);
	free(to_free->str);
	free(to_free);
}
