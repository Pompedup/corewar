/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pos.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 16:29:18 by abezanni          #+#    #+#             */
/*   Updated: 2018/10/15 15:39:56 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static t_bool	verif_syntax_label(t_record *record, char *str, size_t *len)
{
	*len = 0;
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

t_bool			get_label_pos(t_record *record, t_elem *elem, t_arg *arg)
{
	char	*str;
	size_t	len;

	str = elem->line;
	str++;
	if (!(verif_syntax_label(record, elem->line + 1, &len)))
		return (FALSE);
	get_label(record, arg, elem->line + 1, len);
	if (!arg->handled)
		elem->complete = FALSE;
	while (*elem->line && !ft_isspace(*elem->line)
		&& *elem->line != SEPARATOR_CHAR)
		elem->line++;
	return (TRUE);
}

t_bool			get_pos(t_record *record, t_elem *elem, t_arg *arg)
{
	size_t	len;

	ft_strnbrlen(elem->line, &len);
	if ((len == 1 && *elem->line == '-') || len == 0)
	{
		ft_putendl("you try to trick me mother fucker");
		(void)record;
		return (FALSE);
	}
	if (elem->line[len] && !ft_isspace(elem->line[len])
		&& elem->line[len] != SEPARATOR_CHAR)
	{
		ft_printf("[%c]", elem->line[len]);
		ft_putendl("TU SAIS PAS CE QUE C'EST UN CHIFFRE !?");
		return (FALSE);
	}
	if (!ft_strisint(elem->line, len) && !ft_strisuint(elem->line, len))
	{
		ft_putendl("trop gros !!");
		return (FALSE);
	}
	arg->value = ft_atoi(elem->line);
	elem->line += len;
	arg->handled = TRUE;
	return (TRUE);
}

static void		error_dir_ind()
{
	if (arg->type == 2)
	{
		if (!ft_isspace(*elem->line) && *elem->line != SEPARATOR_CHAR)
		{
			ending_str(elem->line);
			ft_printf(BADDATA, record->file_name, record->file.index_line, DIRECT_CHAR, elem->line - (arg->type == 2));
		}
		else
		{
			ending_str(elem->line);
			ft_printf(MISSDIR, record->file_name, record->file.index_line, DIRECT_CHAR);
		}
		return ;
	}
	if (!ft_isspace(*elem->line) && *elem->line != SEPARATOR_CHAR)
	{
		ending_str(elem->line);
		ft_printf(BADDATA, record->file_name, record->file.index_line, DIRECT_CHAR, elem->line - 1);
	}
	else
	{
		ending_str(elem->line);
		ft_printf(MISSIND, record->file_name, record->file.index_line, 'g');
	}
}

t_bool			get_answer(t_record *record, t_elem *elem, t_arg *arg)
{
	if (*elem->line == ':')
		get_label_pos(record, elem, arg);
	else if (ft_isdigit(*elem->line) || *elem->line == '-')
		get_pos(record, elem, arg);
	else
	{
		error_dir_ind(t_record *record, t_elem *elem);
		return (FALSE);
	}
	return (TRUE);
}
