/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_file.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 15:46:56 by abezanni          #+#    #+#             */
/*   Updated: 2018/10/18 18:00:09 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static t_bool	uninteresting_line(t_file *file, t_bool infos)
{
	char *tmp;

	if (!file->line)
		return (FALSE);
	if (infos)
		return (TRUE);
	file->current = file->line;
	while (ft_isspace(*file->current))
		file->current++;
	if (!*file->current || *file->current == COMMENT_CHAR)
	{
		ft_strdel(&(file->line));
		return (FALSE);
	}
	if ((tmp = ft_strchr(file->current, COMMENT_CHAR)))
		*tmp = '\0';
	return (TRUE);
}

void			read_t_file(t_record *record, t_file *file, t_bool info)
{
	int ret;

	file->index_char = 0;
	ft_strdel(&(file->line));
	while (!uninteresting_line(file, info))
	{
		if ((ret = get_next_line(file->fd, &(file->line))) == -1)
		{
			ft_printf(READ, record->file_name);
			return ;
		}
		else if (!ret)
			return ;
		file->current = file->line;
		file->index_line++;
	}
}

void			del_t_file(t_file *file)
{
	close(file->fd);
	get_next_line(file->fd, NULL);
	free(file->line);
}

void			new_t_file(t_record *record, t_file *file, char *file_name)
{
	if ((file->fd = open(file_name, O_RDONLY)) == -1)
	{
		ft_printf(OPEN, record->file_name);
		return ;
	}
	read_t_file(record, file, FALSE);
	if (!file->line)
		ft_printf(EMPTY, record->file_name);
}
