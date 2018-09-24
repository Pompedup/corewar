/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 16:34:11 by abezanni          #+#    #+#             */
/*   Updated: 2018/09/24 13:21:33 by abezanni         ###   ########.fr       */
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
	free(record->name);
	free(record->comment);
	del_t_file(&record->file);
	del_t_functions(&record->functions);
}

void	init(t_record *record, char *file_name)
{
	ft_bzero(record, sizeof(t_record));
	new_t_file(record, &record->file, file_name);
}
