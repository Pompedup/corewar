/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_infos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 17:02:50 by pompedup          #+#    #+#             */
/*   Updated: 2018/09/03 21:39:37 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*search_begin(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	return (line);
}

int		get_string(char *str, char **addr_dest)
{
	char *quote;

	if (*addr_dest)
	{
		if (((quote = ft_strchr(str, '"'))))
		{
			*quote = '\0';
			if (*(++quote))
				quote = search_begin(quote);
			if (*quote)
			{
				ft_putendl("here?");
				return (YET);//Suppression + nommer l'erreur
			}
			*addr_dest = ft_strmjoin(*addr_dest, str, 1);
		}
		else
			*addr_dest = ft_strmjoin(*addr_dest, str, 1);
	}
	else
	{
		str = search_begin(str);
		if (*str != '"')
			return (YET);//Suppression + nommer l'erreur
		str++;
		if (((quote = ft_strchr(str, '"'))))
			*addr_dest = ft_strndup(str, quote - str);
		else
			*addr_dest = ft_strdup(str);
	}
	return (OK);
}

void	get_infos(t_record *record)
{
	char	*begin;
	int		ret;
	t_lines	**first;

	first = &(record->lines);
	while (!(record->name && record->comment))
	{
		begin = search_begin((*first)->str);
		if (!ft_strncmp(begin, NAME_CMD_STRING, 5))
		{
			begin += 5;
			while ((ret = get_string(begin, &(record->name))) > 0)
			{
				del_t_line(first);
				begin = (*first)->str;
			}
		}
		else if (!ft_strncmp(begin, COMMENT_CMD_STRING, 7))
		{
			begin += 8;
			while ((ret = get_string(begin, &(record->comment))) > 0)
			{
				del_t_line(first);
				begin = (*first)->str;
			}
		}
		else
			return ;
		del_t_line(first);
	}
}
