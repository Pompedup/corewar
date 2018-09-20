/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_infos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 17:02:50 by pompedup          #+#    #+#             */
/*   Updated: 2018/09/20 18:46:25 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
**	get the values between 2 quote
*/

static int		get_string(char *str, char **addr_dest)
{
	char *quote;

	if (!addr_dest)
	{
		if (*str != '"')
			return (YET);//IL MANQUE LE NOM/COMMENTAIRE
		str++;
		if (((quote = ft_strchr(str, '"'))))
			*addr_dest = ft_strndup(str, quote - str);
		else
			*addr_dest = ft_strdup(str);
	}
	if (*addr_dest)
	{
		if (((quote = ft_strchr(str, '"'))))
		{
			*quote = '\0';
			if (*(++quote))
				quote = search_begin(quote);
			if (*quote)
			{
				ft_putendl("here?");
				return (YET);//LE NOM/COMMENTAIRE N'EST PAS FINIT
			}
			*addr_dest = ft_strmjoin(*addr_dest, str, 1);
		}
		else
			*addr_dest = ft_strmjoin(*addr_dest, str, 1);
	}
	return (OK);
}

/*
**	Verify if dest is already alocated and if the line contain in first
**	position the cmp str
**	If yes, it complete the dest associated and return TRUE
**	Else, it return FALSE
*/

static void		check_line(t_record *record, t_file *file, char *cmp, char **dest)
{
	size_t len;

	len = ft_strlen(cmp);
	if (*dest)
		return (FALSE);
	if (!ft_strncmp(file->line + file->index_char, cmp, len))
	{
		file->index_char += len;
		while (get_string(file, dest) > 0)
			read_t_file(record, file);
		return (TRUE);
	}
	return (FALSE);
}

/*
**	Take the lines while the name and the comment arn't complete or
**	that check_line return FALSE for both
*/

void			get_infos(t_record *record, t_file *file)
{
	char	*begin;

	while (!(record->name && record->comment))
	{
		read_t_file(record, file);
		if (!check_line(record, file, NAME_CMD_STRING, &(record->comment)))
			if(!check_line(record, file, NAME_CMD_STRING, &(record->comment)))
				return ;
	}
}
