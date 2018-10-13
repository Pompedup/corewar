/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_string.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 18:52:42 by abezanni          #+#    #+#             */
/*   Updated: 2018/10/13 17:43:22 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
**	get the values between 2 quote
*/

char		skip_spaces(char **str, t_file *file)
{
	while (ft_isspace(str ? **str : *file->current))
		str ? (*str)++ : file->current++;
	return (str ? **str : *file->current);
}
//gestion de la taille
/* ************************************************************************** */
static int	handle_end_string(t_record *record, t_file *file, t_string *data, char *quote)
{
	*quote = '\0';
	if ((data->size += quote - file->current) >  data->max)
	{
		ft_printf(LONG, record->file_name, file->index_line, data->type, data->max, data->size);
		return (-1);
	}
	quote++;
	skip_spaces(&quote, NULL);
	if (*quote && *quote != '#')
	{
		ft_printf(AFTER, record->file_name, file->index_line, data->type, quote);
		return (-1);
	}
	ft_strcpy(data->addr, file->current);
	return (1);
}

static int	handle_string(t_record *record, t_file *file, t_string *data)
{
	char *quote;

	if (((quote = ft_strchr(file->current, '"'))))
		return (handle_end_string(record, file, data, quote));
	if (!((data->size += ft_strlen(file->current) + 1) > data->max))
	{
		data->addr = ft_stpcpy(data->addr, file->current);
		data->addr = ft_stpcpy(data->addr, "\n");
	}
	read_t_file(record, file, TRUE);
	return (0);
}

t_bool		get_string(t_record *record, t_file *file, t_string *data)
{
	int		ret;

	file->current = file->line + file->index_char;
	if (skip_spaces(NULL, file) != '"')
	{
		ft_printf(BEGIN, record->file_name, file->index_line, data->type);
		return (FALSE);
	}
	file->current++;
	while (file->line)
	{
		if ((ret = handle_string(record, file, data)) == 1)
			return (TRUE);
		else if (ret == -1)
			return (FALSE);
	}
	ft_printf(ENDING, record->file_name, data->index_line, data->type);
	return (FALSE);
}
