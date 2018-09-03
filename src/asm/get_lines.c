/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_lines.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 15:27:07 by pompedup          #+#    #+#             */
/*   Updated: 2018/09/03 18:50:31 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	uninteresting_line(char **line)
{
	ft_strdel(line);
	return (OK);
}

static int	select_line(char **line)
{
	char	*hash;
	int		i;
	int		size;

	i = 0;
	hash = NULL;
	while ((*line)[i] == ' ' || (*line)[i] == '\t')
		i++;
	if (!(*line)[i] || (*line)[i] == '#')
		return (uninteresting_line(line));
	if ((hash = ft_strchr(*line + i, '#')))
	{
		size = hash - *line;
		hash = *line;
		*line = ft_strndup(*line, size);
		free(hash);
		if (!*line)
			return (ALLOC_ERROR);
	}
	return (OK);
}

static int	close_file(int fd, int back)
{
	close(fd);
	return (back);
}

int			get_lines(char *file_name, t_lines **current)
{
	int		fd;
	int		ret;
	int		i;
	char	*line;

	if ((fd = open(file_name, O_RDONLY)) == -1)
		return (NO_FILE);
	i = 0;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		ret = select_line(&line);
		if (ret)
			return (close_file(fd, ret));
		if (line)
		{
			new_t_line(current, line, i);
			if (!*current)
				return (ALLOC_ERROR);
		}
		i++;
	}
	if (ret == -1)
		return (CANT_READ);
	return (close_file(fd, OK));
}
