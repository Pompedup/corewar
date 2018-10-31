/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_string.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 18:52:42 by abezanni          #+#    #+#             */
/*   Updated: 2018/10/21 15:26:21 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
**	Skip the spaces of a line and return the first char found after theses
**	spaces
*/

char		skip_spaces(char **str)
{
	while (ft_isspace(**str))
		(*str)++;
	return (**str);
}

/*
**	Verify if there is nothing wrong (Too long string of something write after
**	the ending quote) end copy the line if it's good.
*/

static int	handle_end_string(t_record *record, t_file *file, t_string *data,\
																char *quote)
{
	*quote = '\0';
	if ((data->size += quote - file->current) > data->max)
	{
		ft_printf(LONG, record->file_name, data->index_line, data->type,\
			data->max, data->size);
		return (-1);
	}
	quote++;
	skip_spaces(&quote);
	if (*quote && *quote != '#')
	{
		ft_printf(AFTER, record->file_name, file->index_line, data->type,\
			quote);
		return (-1);
	}
	ft_strcpy(data->addr, file->current);
	return (1);
}

/*
**	Check if there is the ending quote in the current line
**			-> call the function handle_end_string
**	Else
**			-> check if this is not to big
**					-> copy the line in the current addr
**	Read the file
*/

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

/*
**	Call skip spaces and verify if the first char is a quote
**			!->	end
**	Turn in a loop until handle_string found the end
**			-> next step
**	or there is no line
**			!-> end
*/

t_bool		get_string(t_record *record, t_file *file, t_string *data)
{
	int		ret;

	file->current = file->line + file->index_char;
	if (skip_spaces(&file->current) != '"')
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
