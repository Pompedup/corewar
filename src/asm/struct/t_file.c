/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_file.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 15:46:56 by abezanni          #+#    #+#             */
/*   Updated: 2018/09/20 15:50:29 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	del_t_file(t_file *file)
{
	close(file->fd);
	get_next_line(file->fd, NULL);
	free(file->line);
}

void	new_t_file(t_file *file, char *file_name)
{
	if ((file->fd = open(file_name, O_RDONLY)) == -1)
		error(NO_FILE);
}
