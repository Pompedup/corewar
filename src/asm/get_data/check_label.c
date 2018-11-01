/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_label.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecesari <ecesari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 16:07:43 by abezanni          #+#    #+#             */
/*   Updated: 2018/11/01 15:27:25 by ecesari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
********************************************************************************
**	Move the cursor of file->current to the next char after the name
********************************************************************************
*/

static void		next_data(t_file *file, char *name)
{
	int i;

	i = file->index_char + ft_strlen(name) + 1;
	while (ft_isspace(file->line[i]))
		i++;
	file->index_char = i;
	file->current = file->line + file->index_char;
}

/*
********************************************************************************
**	Check if the name isn't already know
**	If not, create a copy of the name
********************************************************************************
*/

static t_bool	is_new_name(t_record *record, char *str, char **name)
{
	t_function *functions;

	functions = record->functions;
	while (functions)
	{
		if (!ft_strcmp(functions->name, str))
			return (TRUE);
		functions = functions->next;
	}
	if (!(*name = ft_strdup(str)))
	{
		ft_printf(ALLOC, record->name);
		erase(record);
		exit(0);
	}
	return (TRUE);
}

/*
********************************************************************************
**	Verify if the ":" arn't at the beggining of a line
********************************************************************************
*/

t_bool			verify_label(t_record *record, t_file *file, int end,\
																char **name)
{
	if (end)
	{
		file->current[end] = '\0';
		if (ft_strisall(file->current, &is_label_char))
		{
			if (!(is_new_name(record, file->current, name)))
				return (FALSE);
		}
		file->current[end] = LABEL_CHAR;
	}
	else
	{
		ft_printf(NOLABEL, record->file_name, file->index_line, LABEL_CHAR);
		return (FALSE);
	}
	return (TRUE);
}

/*
********************************************************************************
**	Check if there is a ":" end if there is a space after
********************************************************************************
*/

t_bool			check_label(t_record *record, t_file *file, char **name)
{
	char	*colon;

	*name = NULL;
	if ((colon = ft_strchr(file->current, LABEL_CHAR)))
	{
		if (!ft_isspace(*(colon + 1)) && *(colon + 1))
			return (TRUE);
		if (!verify_label(record, file, colon - file->current, name))
			return (FALSE);
		if (*name)
			next_data(file, *name);
	}
	return (TRUE);
}
