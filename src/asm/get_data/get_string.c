/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_string.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 18:52:42 by abezanni          #+#    #+#             */
/*   Updated: 2018/10/04 19:04:17 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
**	get the values between 2 quote
*/

int				skip_spaces(char *str)
{
	int i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	return (i);
}
//gestion de la taille
static t_bool	get_end_string(t_record *record, t_file *file, t_string *data)
{
	char *quote;
	int	index_line;

	index_line = file->index_line;
	read_t_file(record, file, TRUE);
	while (file->line)
	{
		if (((quote = ft_strchr(file->line, '"'))))
		{
			*quote = '\0';
			if (*(quote + 1))
			{
				ft_printf(AFTER, record->name_file, index_line, data->type, quote + 1);
				return (FALSE);
			}
			ft_strcpy(data->addr, file->line);
			return (TRUE);
		}
		else
		{
			data->addr = ft_stpcpy(data->addr, file->line);
			data->addr = ft_stpcpy(data->addr, "\n");
		}
		read_t_file(record, file, TRUE);
	}
	ft_printf(ENDING, record->name_file, index_line, data->type);
	return (FALSE);
}

t_bool	get_string(t_record *record, t_file *file, t_string *data)
{
	char *quote;
	char *str;

	str = file->line + file->index_char;
	str += skip_spaces(str);
	if (*str != '"')
	{
		ft_printf(BEGIN, record->name_file, file->index_line, data->type);
		return (FALSE);//IL MANQUE LE NOM/COMMENTAIRE
	}
	str++;
	if (((quote = ft_strchr(str, '"'))))
	{
		if ((data.size = quote - str) >  data->max)
		{
			ft_printf(LONG, record->name_file, file->index_line, data->type, data->max, data.size);
			return (FALSE);
		}
		ft_strncpy(data->addr, str, quote - str);
		return (TRUE);
	}
	data->addr = ft_stpcpy(data->addr, str);
	data->addr = ft_stpcpy(data->addr, "\n");
	return (get_end_string(record, file, data));
}
