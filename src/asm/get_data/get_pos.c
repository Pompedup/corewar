/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pos.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 16:29:18 by abezanni          #+#    #+#             */
/*   Updated: 2018/10/19 20:56:43 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static t_bool	verif_syntax_label(t_record *record, char *str, size_t *len, int erreur)
{
	(void)erreur;

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

static t_bool	get_label_pos(t_record *record, t_elem *elem, t_arg *arg, int erreur)
{
	size_t	len;

	if (!(verif_syntax_label(record, arg->copy + 1, &len, erreur)))
		return (FALSE);
	get_label(record, arg, arg->copy + 1, len);
	if (!arg->handled)
		elem->complete = FALSE;
	return (TRUE);
}

static t_bool	get_pos(t_record *record, t_arg *arg, int erreur)
{
	size_t	len;

	(void)erreur;
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

/*
**	Explain the error found from a dir or a ind
*/

static void		error_dir_ind(t_record *record, t_elem *elem, t_arg *arg, int error)
{
	if (arg->type == 2)
	{
		if (!ft_isspace(*elem->line) && *elem->line != SEPARATOR_CHAR)
			ft_printf(BADDATA, record->file_name, record->file.index_line, DIRECT_CHAR, arg->copy - (arg->type == 2));
		else
			ft_printf(MISSDIR, record->file_name, record->file.index_line, DIRECT_CHAR);
		return ;
	}
	ending_str(elem->line);
	ft_printf(BADDATA, record->file_name, record->file.index_line, DIRECT_CHAR, arg->copy - error);
}

/*
**	Test if the arg contain a label or a int and call the function correspondent
**	else
**		error
*/

t_bool			get_answer(t_record *record, t_elem *elem, t_arg *arg, int erreur)
{
	if (*arg->copy == ':')
	{
		if (!get_label_pos(record, elem, arg, erreur))
			return (FALSE);
	}
	else if (ft_isdigit(*arg->copy) || *arg->copy == '-')
	{
		if (!get_pos(record, arg, erreur))
			return (FALSE);
	}
	else
	{
		error_dir_ind(record, elem, arg, erreur);
		return (FALSE);
	}
	return (TRUE);
}
