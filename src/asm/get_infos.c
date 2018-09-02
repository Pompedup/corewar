/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_infos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 17:02:50 by pompedup          #+#    #+#             */
/*   Updated: 2018/09/02 16:36:37 by abezanni         ###   ########.fr       */
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

	str = search_begin(str);
	if (*str != '"')
	{
		//pas bon format
	}
	str++;
	if (ft_strchr(str, '"'))
	*addr_dest = ft_strdup(str, );
	return (OK);
}

void	get_infos(t_record *record)
{
	char	*begin;
	t_lines	**lines;

	lines = &(record->lines);
	while (!(record->name && record->comment))
	{
		begin = search_begin((*line)->str);
		if (ft_strncmp(begin, NAME_CMD_STRING, 5))
			get_string(begin + 5, &(record->name));
		else if (ft_strncmp(begin, COMMENT_CMD_STRING, 7))
			get_string(begin + 7, &(record->comment));
		else
			return (YET);
		delete_t_lines(lines);
	}
}
