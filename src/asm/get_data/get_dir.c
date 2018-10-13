/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 17:31:48 by abezanni          #+#    #+#             */
/*   Updated: 2018/10/13 16:52:16 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		get_dir(t_record *record, t_arg *current_arg, t_elem *elem, int i)
{
	elem->line++;
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
			ft_printf(MISSDIR, record->file_name, record->file.index_line, DIRECT_CHAR);
		}
		return (FALSE);
	}
	current_arg->type = 2;
	if (g_op_tab[elem->type].dir)
		current_arg->size = 2;
	else
		current_arg->size = 4;
	elem->size += current_arg->size;
	elem->key +=  2 << (6 - (2 * i));
	return (TRUE);
}
