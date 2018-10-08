/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_label.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 16:07:43 by abezanni          #+#    #+#             */
/*   Updated: 2018/10/08 16:36:40 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	next_data(t_file *file, char *name)
{
	int i;

	i = file->index_char + ft_strlen(name) + 1;
	while (ft_isspace(file->line[i]))
		i++;
	file->index_char = i;
	file->current = file->line + file->index_char;
}

static t_bool	is_new_name(t_record *record, char *str, char **name)
{
	t_function *functions;

	functions = record->functions;
	while (functions)
	{
		if (!ft_strcmp(functions->name, str))
			return (TRUE);
		functions = functions->next;
	}
	if (!(*name = ft_strdup(str)))
	{
		ft_printf(ALLOC, record->name);
		return (FALSE);
	}
	return (TRUE);
}

t_bool		verify_label (t_record *record, t_file *file, char *colon, char **name)
{
	int end;

	if ((end = colon - file->current))
	{
		file->current[end] = '\0';
		if (ft_strisall(file->current, &is_label_char))
		{
			if (!(is_new_name(record, file->current, name)))
				return (FALSE);
		}
		file->current[end] = LABEL_CHAR;
	}
	else
	{
		ft_printf(NOLABEL, record->name_file, file->index_line, LABEL_CHAR);
		return (FALSE);
	}
	return (TRUE);
}

t_bool		check_label(t_record *record, t_file *file, char **name)
{
	char	*colon;

	*name = NULL;
	if ((colon = ft_strchr(file->current, LABEL_CHAR)))
	{
		if (!verify_label (record, file, colon, name))
			return (FALSE);
		if (*name)
			next_data(file, *name);
	}
	return (TRUE);
}
