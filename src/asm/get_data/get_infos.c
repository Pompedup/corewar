/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_infos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 17:02:50 by pompedup          #+#    #+#             */
/*   Updated: 2018/10/13 17:41:24 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
********************************************************************************
**	Verify if dest is already alocated and if the line contain in first
**	position the cmp str
**	If yes, it complete the dest associated and return TRUE
**	Else, it return FALSE
********************************************************************************
*/

static t_bool	check_line(t_record *record, t_file *file, char *cmp)
{
	size_t		len;
	t_string	data;

	len = ft_strlen(cmp);
	data.type = cmp;
	data.max = cmp == NAME_CMD_STRING ? PROG_NAME_LENGTH : COMMENT_LENGTH;
	data.addr = cmp == NAME_CMD_STRING ? record->name : record->comment;
	data.size = 0;
	data.index_line = file->index_line;
	if (!ft_strncmp(file->current, cmp, len))
	{
		if (cmp == NAME_CMD_STRING && !record->name_complete)
			record->name_complete = TRUE;
		else if (cmp == COMMENT_CMD_STRING && !record->comment_complete)
			record->comment_complete = TRUE;
		else
		{
			ft_printf(SECOND, record->file_name, file->index_line, data.type);
			return (FALSE);
		}
		file->index_char += len;
		return (get_string(record, file, &data));//cmp, dest));
	}
	return (FALSE);
}

static char		*check_type(char *str)
{
	if (!ft_strncmp(str, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
		return (NAME_CMD_STRING);
	if (!ft_strncmp(str, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)))
		return (COMMENT_CMD_STRING);
	return (NULL);
}

/*
********************************************************************************
**	Take the lines while the name and the comment arn't complete or
**	that check_line return FALSE for both
********************************************************************************
*/

t_bool			get_infos(t_record *record, t_file *file)
{
	char *type;

	while (file->line && (type = check_type(file->current)))
	{
		if (!check_line(record, file, type))
			return (FALSE);
		read_t_file(record, file, FALSE);
	}
	return (TRUE);
}

//	\033[48;2;%d;%d;%dm
//	\033[38;2;%d;%d;%dm
