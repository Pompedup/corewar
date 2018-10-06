/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 16:34:11 by abezanni          #+#    #+#             */
/*   Updated: 2018/10/06 19:08:01 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	error(t_record *record, int error)
{
	(void)error;
	erase(record);
	exit(0);
}

void	erase(t_record *record)
{
	del_t_file(&record->file);
	del_t_functions(&record->functions);
}

t_bool	init(t_record *record, char *file_name)
{
	ft_bzero(record, sizeof(t_record));
	record->name_file = file_name;
	new_t_file(record, &record->file, file_name);
	if (record->file.fd == -1 || !record->file.line)
		return (FALSE);
	return (TRUE);
}
