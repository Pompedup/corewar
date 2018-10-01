/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_infos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 17:02:50 by pompedup          #+#    #+#             */
/*   Updated: 2018/10/01 16:07:04 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
**	get the values between 2 quote
*/

int				skip_spaces(char *str)
{
	int i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	return (i);
}

// a verifier
static t_bool	get_string(char *str, char *addr_dest, t_file *file)
{
	char *quote;


	str += skip_spaces(str);
	if (*str != '"')
	{
		ft_putendl("Mauvaise ligne");
		return (FALSE);//IL MANQUE LE NOM/COMMENTAIRE
	}
	str++;
	if (((quote = ft_strchr(str, '"'))))
		ft_strncat(addr_dest, str, quote - str);
	else
	{
		ft_strcat(addr_dest, str);
		while (TRUE)
		{
			read_t_file(record, file);

		}
	}
	else if (*addr_dest)
	{
		if (((quote = ft_strchr(str, '"'))))
		{
			if (*(quote + 1))
				return (YET);//mauvaise fin de ligne
			*quote = '\0';
			*addr_dest = ft_strmjoin(*addr_dest, str, 1);
		}
		else
		{
			*addr_dest = ft_strmjoin(*addr_dest, str, 1);
			return (45);
		}
	}
	return (OK);
}

/*
**	Verify if dest is already alocated and if the line contain in first
**	position the cmp str
**	If yes, it complete the dest associated and return TRUE
**	Else, it return FALSE
*/

static t_bool	check_line(t_record *record, t_file *file, char *cmp,\
					char *dest)
{
	size_t len;

	len = ft_strlen(cmp);
	if (!ft_strncmp(file->line + file->index_char, cmp, len))
	{
		if (cmp == NAME_CMD_STRING && !record->name_complete)
			record->name_complete = TRUE;
		else if (!record->comment_complete)
			record->comment_complete = TRUE;
		else
			exit(0);//gerer lerreur
		file->index_char += len;
		return (get_string(file->line + file->index_char, dest, file));
	}
	return (FALSE);
}

/*
**	Take the lines while the name and the comment arn't complete or
**	that check_line return FALSE for both
*/

t_bool			get_infos(t_record *record, t_file *file)
{
	while (file->line && !(record->name && record->comment))
	{
		if (!check_line(record, file, NAME_CMD_STRING, record->name))
			if(!check_line(record, file, COMMENT_CMD_STRING, record->comment))
				return (FALSE);
		read_t_file(record, file);
	}
	return (TRUE);
}


// 4
//Nom max length 128 + 4 + 4
//comment max length 2048 + 4
