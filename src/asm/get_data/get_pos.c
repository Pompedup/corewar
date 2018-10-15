/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pos.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 16:29:18 by abezanni          #+#    #+#             */
/*   Updated: 2018/10/15 18:39:32 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static t_bool	verif_syntax_label(t_record *record, char *str, size_t *len)
{
	*len = 0;
	while (str[*len])
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
	size_t	len;

	if (!(verif_syntax_label(record, arg->copy + 1, &len)))
		return (FALSE);
	get_label(record, arg, arg->copy + 1, len);
	if (!arg->handled)
		elem->complete = FALSE;
	return (TRUE);
}

t_bool			get_pos(t_record *record, t_arg *arg)
{
	size_t	len;

	len = *arg->copy == '-' ? 1 : 0;
	while (arg->copy[len])
	{
		if (!ft_isdigit(arg->copy[len]))
		{
			ft_printf("[%c]", arg->copy[len]);
			ft_putendl("TU SAIS PAS CE QUE C'EST UN CHIFFRE !?");
			return (FALSE);
		}
		len++;
	}
	if ((len == 1 && *arg->copy == '-') || len == 0)
	{
		ft_putendl("you try to trick me mother fucker");
		(void)record;
		return (FALSE);
	}
	if (!ft_strisint(arg->copy, len) && !ft_strisuint(arg->copy, len))
	{
		ft_putendl("trop gros !!");
		return (FALSE);
	}
	arg->value = ft_atoi(arg->copy);
	arg->handled = TRUE;
	return (TRUE);
}

static void		error_dir_ind(t_record *record, t_elem *elem, t_arg *arg)
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
	ending_str(elem->line);
	ft_printf(BADDATA, record->file_name, record->file.index_line, DIRECT_CHAR, elem->line - 1);
}

t_bool			get_answer(t_record *record, t_elem *elem, t_arg *arg)
{
	if (*arg->copy == ':')
	{
		if (!get_label_pos(record, elem, arg))
			return (FALSE);
	}
	else if (ft_isdigit(*arg->copy) || *arg->copy == '-')
	{
		if (!get_pos(record, arg))
			return (FALSE);
	}
	else
	{
		error_dir_ind(record, elem, arg);
		return (FALSE);
	}
	return (TRUE);
}
