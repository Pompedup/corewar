/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_file.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 15:46:56 by abezanni          #+#    #+#             */
/*   Updated: 2018/10/04 17:07:51 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static t_bool	uninteresting_line(t_file *file, t_bool infos)
{
	if (!file->line)
		return (FALSE);
	if (infos)
		return (TRUE);
	while (ft_isspace(file->line[file->index_char]))
		file->index_char++;
	if (!file->line[file->index_char] || file->line[file->index_char] == '#')
	{
		ft_strdel(&(file->line));
		return (FALSE);
	}
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
			error(record, INVALID_FILE);
		else if (!ret)
			return ;
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
	//record->name = file_name;
	if ((file->fd = open(file_name, O_RDONLY)) == -1)
		error(record, NO_FILE);
	read_t_file(record, file, FALSE);
}
