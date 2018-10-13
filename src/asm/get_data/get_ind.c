/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ind.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 17:31:14 by abezanni          #+#    #+#             */
/*   Updated: 2018/10/13 16:52:25 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int				get_ind(t_record *record, t_arg *current_arg, t_elem *elem, int i)
{
	if (*elem->line == ':')
		get_label_pos(record, elem, current_arg);
	else if (ft_isdigit(*elem->line) || *elem->line == '-')
		get_pos(record, elem, current_arg);
	else
	{
		if (!ft_isspace(*elem->line) && *elem->line != SEPARATOR_CHAR)
		{
			ending_str(elem->line);
			ft_printf(BADDATA, record->file_name, record->file.index_line, DIRECT_CHAR, elem->line - 1);
		}
		else
		{
			ending_str(elem->line);
			ft_printf(MISSIND, record->file_name, record->file.index_line, 'g');
		}
		return (FALSE);
	}
	current_arg->type = 4;
	current_arg->size = 2;
	elem->size += 2;
	elem->key += 3 << (6 - (2 * i));
	return (TRUE);
}
