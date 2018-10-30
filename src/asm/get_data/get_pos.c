/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pos.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 16:29:18 by abezanni          #+#    #+#             */
/*   Updated: 2018/10/30 18:40:40 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
********************************************************************************
********************************************************************************
*/

static t_bool	verif_syntax_label(t_record *record, char *str, size_t *len,\
																	char *copy)
{
	*len = 0;
	while (str[*len])
	{
		if (!(is_label_char(str[*len])))
		{
			ft_printf(WRLABEL, record->file_name, record->file.index_line,\
													str[*len], copy);
			return (FALSE);
		}
		(*len)++;
	}
	if (!*len)
	{
		ft_printf(MISSBGNLAB, record->file_name, record->file.index_line,
																LABEL_CHAR);
		return (FALSE);
	}
	return (TRUE);
}

/*
********************************************************************************
********************************************************************************
*/

static t_bool	get_label_pos(t_record *record, t_elem *elem, t_arg *arg)
{
	size_t	len;

	arg->str++;
	if (!(verif_syntax_label(record, arg->str, &len, arg->copy)))
		return (FALSE);
	get_label(record, arg, arg->str, len);
	if (!arg->handled)
		elem->complete = FALSE;
	return (TRUE);
}

/*
********************************************************************************
********************************************************************************
*/

static t_bool	get_nbr_pos(t_record *record, t_arg *arg)
{
	size_t	len;

	len = *arg->str == '-' ? 1 : 0;
	while (arg->str[len])
	{
		if (!ft_isdigit(arg->str[len]))
		{
			ft_printf(NOTNBR, record->file_name, record->file.index_line,\
											arg->str[len], arg->copy);
			return (FALSE);
		}
		len++;
	}
	if ((len == 1 && *arg->str == '-') || len == 0)
	{
		ft_printf(MISSNBR, record->file_name, record->file.index_line);
		return (FALSE);
	}
	if (!ft_strisint(arg->str, len) && !ft_strisuint(arg->str, len))
	{
		ft_printf(INTTOOBIG, record->file_name, record->file.index_line,\
					*arg->str == '-' ? "little" : "big", arg->copy);
		return (FALSE);
	}
	return (TRUE);
}

/*
********************************************************************************
**	Explain the error found from a dir or a ind
********************************************************************************
*/

static void		error_dir_ind(t_record *record, t_elem *elem, t_arg *arg)
{
	if (arg->type == 2)
	{
		if (!ft_isspace(*elem->line) && *elem->line != SEPARATOR_CHAR)
			ft_printf(BADDATA, record->file_name, record->file.index_line,\
													DIRECT_CHAR, arg->copy);
		else
			ft_printf(MISSDIR, record->file_name, record->file.index_line,\
																DIRECT_CHAR);
		return ;
	}
	ending_str(elem->line);
	ft_printf(BADDATA, record->file_name, record->file.index_line, DIRECT_CHAR,
															arg->copy);
}

/*
********************************************************************************
**	Test if the arg contain a label or a int and call the function correspondent
**	else
**		error
********************************************************************************
*/

t_bool			get_pos(t_record *record, t_elem *elem, t_arg *arg)
{
	if (*arg->str == ':')
	{
		if (!get_label_pos(record, elem, arg))
			return (FALSE);
	}
	else if (ft_isdigit(*arg->str) || *arg->str == '-')
	{
		if (!get_nbr_pos(record, arg))
			return (FALSE);
		else
		{
			arg->value = ft_atoi(arg->str);
			arg->handled = TRUE;
		}
	}
	else
	{
		error_dir_ind(record, elem, arg);
		return (FALSE);
	}
	return (TRUE);
}
