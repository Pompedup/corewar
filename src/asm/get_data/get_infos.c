/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_infos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 17:02:50 by pompedup          #+#    #+#             */
/*   Updated: 2018/10/30 18:39:22 by abezanni         ###   ########.fr       */
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
		return (get_string(record, file, &data));
	}
	return (FALSE);
}

/*
********************************************************************************
**	Verify if it's a name or a comment or an error
********************************************************************************
*/

static t_bool	check_type(t_file *file, char **type)
{
	*type = NULL;
	while (ft_isspace(*file->current))
	{
		file->current++;
		file->index_char++;
	}
	if (!ft_strncmp(file->current, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
	{
		*type = NAME_CMD_STRING;
		return (TRUE);
	}
	if (!ft_strncmp(file->current, COMMENT_CMD_STRING,
												ft_strlen(COMMENT_CMD_STRING)))
	{
		*type = COMMENT_CMD_STRING;
		return (TRUE);
	}
	if (*file->current == '#' || *file->current == '\0')
		return (TRUE);
	return (FALSE);
}

/*
********************************************************************************
**	Replace the hashtag by a end char and replace the cursor of
**	file->current after the first sapces
********************************************************************************
*/

static void		remove_hash(t_record *record, t_file *file)
{
	char *tmp;

	while (ft_isspace(*file->current))
		file->current++;
	if (!*file->current || *file->current == COMMENT_CHAR)
		read_t_file(record, file, FALSE);
	else if ((tmp = ft_strchr(file->current, COMMENT_CHAR)))
		*tmp = '\0';
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

	while (file->line && check_type(file, &type))
	{
		if (type)
			if (!check_line(record, file, type))
				return (FALSE);
		read_t_file(record, file, TRUE);
	}
	remove_hash(record, file);
	return (TRUE);
}
