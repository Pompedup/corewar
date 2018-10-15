/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 15:26:00 by abezanni          #+#    #+#             */
/*   Updated: 2018/10/15 18:01:03 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static t_bool	handle_elem(t_record *record, t_file *file, t_elem **elem)
{
	int			type;

	if ((get_type(record, file, &type)))
	{
		if (g_op_tab[type].shortcut)
		{
			if (!(new_t_elem(record, elem, type)))
				return (FALSE);
			(*elem)->index_line = file->index_line;
			(*elem)->line = file->current + ft_strlen((*elem)->op_case.shortcut);
			if (!get_elem(record, *elem))
				return (FALSE);
			record->tot += (*elem)->size;
		}
		return (TRUE);
	}
	return (FALSE);
}

t_bool			get_functions(t_record *record, t_file *file,\
				t_function **current_function)
{
	t_elem		**current_elem;
	char		*name;

	while (file->line)
	{
		if (!check_label(record, file, &name))
			return (FALSE);
		if (name || !(*current_function))
		{
			if (*current_function)
				current_function = &((*current_function)->next);
			if (!new_t_function(record, current_function, name))
				return (FALSE);
			current_elem = &((*current_function)->elems);
		}
		if (!(handle_elem(record, file, current_elem)))
			return (FALSE);
		if (*current_elem)
			current_elem = &((*current_elem)->next);
		read_t_file(record, file, FALSE);
	}
	return (TRUE);
}
