/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pos.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 16:29:18 by abezanni          #+#    #+#             */
/*   Updated: 2018/10/13 15:49:45 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static t_bool	verif_syntax_label(t_record *record, char *str, size_t *len)
{
	*len = 0;
	ft_putendl("vrai?");
	while (str[*len] && str[*len] != SEPARATOR_CHAR && !ft_isspace(str[*len]))
	{
		if (!(is_label_char(str[*len])))
		{
			ft_putendl("mauvais caractere");
			return (FALSE);
		}
		(*len)++;
	}
	if (!*len)
	{
		ft_putendl("aucun label");
		return (FALSE);
		(void)record;
	}
	return (TRUE);
}

t_bool			get_label_pos(t_record *record, t_elem *elem, t_arg *current_arg)
{
	char	*str;
	size_t	len;

	str = elem->line;
	str++;
	if (!(verif_syntax_label(record, elem->line + 1, &len)))
		return (FALSE);
	if (!(get_label(record, current_arg, elem->line + 1, len)))
		return (FALSE);
	if (!current_arg->handled)
		elem->complete = FALSE;
	while (*elem->line && *elem->line != SEPARATOR_CHAR)
		elem->line++;
	return (TRUE);
}

t_bool			get_pos(t_record *record, t_elem *elem, t_arg *current_arg)
{
	//char	*str;
	size_t	len;

	ft_strnbrlen(elem->line, &len);
	if ((len == 1 && *elem->line == '-') || len == 0)
	{
		ft_putendl("you try to trick me mother fucker");
		(void)record;
		return (FALSE);
	}
	if (elem->line[len] && !ft_isspace(elem->line[len]) && elem->line[len] != SEPARATOR_CHAR)
	{
		ft_printf("[%c]", elem->line[len]);
		ft_putendl("TU SAIS PAS CE QUE C'EST UN CHIFFRE !?");
		return (FALSE);
	}
	if (!ft_isint(elem->line, len))
	{
		ft_putendl("trop gros !!");
		return (FALSE);
	}
	current_arg->value = ft_atoi(elem->line);
	elem->line += len;
	current_arg->handled = TRUE;
	return (TRUE);
}
