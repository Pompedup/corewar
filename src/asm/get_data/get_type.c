/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 16:01:44 by abezanni          #+#    #+#             */
/*   Updated: 2018/10/21 16:16:29 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_bool		cmp_instruction(char *str, char *shortcut, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		if (str[i] != shortcut[i])
			return (FALSE);
		i++;
	}
	if (ft_isalpha(str[i]))
		return (FALSE);
	return (TRUE);
}

void		handle_bad_end(t_record *record, t_file *file, int i)
{
	file->current[i++] = '\0';
	while (ft_isspace(file->current[i]))
		i++;
	if (file->current[i] == LABEL_CHAR)
		ft_printf(SPACES, record->file_name, file->index_line, file->current,\
			LABEL_CHAR);
	else
		ft_printf(MISSLAB, record->file_name, file->index_line, LABEL_CHAR,\
			file->current);
}

void		handle_bad_char(t_record *record, t_file *file, int i)
{
	char	c;

	c = file->current[i];
	while (file->current[i] && !ft_isspace(file->current[i])\
		&& file->current[i] != LABEL_CHAR)
		i++;
	file->current[i] = '\0';
	ft_printf(WRLABEL, record->file_name, file->index_line, c, file->current);
}

void		handle_error(t_record *record, t_file *file)
{
	int		i;

	i = 0;
	while (file->current[i])
	{
		if (ft_isspace(file->current[i]))
		{
			handle_bad_end(record, file, i);
			return ;
		}
		if (!is_label_char(file->current[i]))
		{
			handle_bad_char(record, file, i);
			return ;
		}
		i++;
	}
	ft_printf(MISSLAB, record->file_name, file->index_line, LABEL_CHAR,\
		file->current);
}

t_bool		get_type(t_record *record, t_file *file, int *type)
{
	if (!*file->current)
	{
		*type = 16;
		return (TRUE);
	}
	*type = 0;
	while (g_op_tab[*type].shortcut)
	{
		if (cmp_instruction(file->current, g_op_tab[*type].shortcut,\
			ft_strlen(g_op_tab[*type].shortcut)))
			return (TRUE);
		(*type)++;
	}
	handle_error(record, file);
	return (FALSE);
}
