/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_lines.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pompedup <pompedup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 15:27:07 by pompedup          #+#    #+#             */
/*   Updated: 2018/09/01 16:58:19 by pompedup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		add_line(char *line, t_lines **lines)
{
	t_lines *new;

	if (!(new = malloc(sizeof(t_lines))))
		return (ALLOC_ERROR);
	new->str = line;
	new->next = NULL;
	*lines = new;
	return (OK);
}

int		uninteresting_line(char **line)
{
	ft_strdel(line);
	return (OK);
}

int		select_line(char **line)
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

int		get_lines(char *file_name, t_lines **lines)
{
	int		fd;
	int		ret;
	char	*line;

	if ((fd = open(file_name, O_RDONLY)) == -1)
		return (NO_FILE);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		ret = select_line(&line);
		if (ret)
		{
			close(fd);
			return (ret);
		}
		if (line)
		{
			if ((ret = add_line(line, lines)))
				return (ret);
			lines = &((*lines)->next);
		}
	}
	if (ret == -1)
		return (CANT_READ);
	close(fd);
	return (OK);
}
