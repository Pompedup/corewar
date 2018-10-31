/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_elem_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 18:54:37 by abezanni          #+#    #+#             */
/*   Updated: 2018/10/31 17:13:17 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
********************************************************************************
********************************************************************************
*/

static t_bool	check_existing_type(t_record *record, t_elem *elem, t_arg *arg,\
																	char *str)
{
	if (*str == 'r')
		arg->type = 1;
	else if (*str == DIRECT_CHAR)
		arg->type = 2;
	else if (*str == '-' || ft_isdigit(*str) || *str == LABEL_CHAR)
		arg->type = 4;
	else
	{
		ft_printf(UKARG, record->file_name, elem->index_line, str);
		return (FALSE);
	}
	return (TRUE);
}

/*
********************************************************************************
********************************************************************************
*/

static t_bool	verify_args_type(t_record *record, t_elem *elem)
{
	int		i;
	t_arg	**arg;
	char	**split;

	i = 0;
	arg = &(elem->args);
	split = elem->split;
	while (split[i])
	{
		new_t_arg(arg, elem->addr, split[i]);
		if (!(check_existing_type(record, elem, *arg, split[i])))
			return (FALSE);
		if (!(elem->op_case.accept[i] & (*arg)->type))
		{
			error_type(record, elem, *arg, i);
			return (FALSE);
		}
		arg = &((*arg)->next);
		i++;
	}
	return (TRUE);
}

/*
********************************************************************************
********************************************************************************
*/

static t_bool	verify_present_arg(t_record *record, t_elem *elem, char c)
{
	if (!c || c == SEPARATOR_CHAR)
	{
		if (!c)
			ft_printf(MISSARG, record->file_name, record->file.index_line,\
				elem->op_case.shortcut, elem->op_case.nbr_arg, 0);
		else
			ft_printf(ARGBEFSEP, record->file_name, elem->index_line);
		return (FALSE);
	}
	return (TRUE);
}

/*
********************************************************************************
********************************************************************************
*/

static t_bool	verify_args_separators(t_record *record, t_elem *elem,\
																	char *str)
{
	char	c;

	c = skip_spaces(&str);
	if (!verify_present_arg(record, elem, c))
		return (FALSE);
	while (*str && !ft_isspace(*str) && *str != SEPARATOR_CHAR)
		str++;
	while ((c = skip_spaces(&str)))
	{
		if (c != SEPARATOR_CHAR)
		{
			ft_printf(MISSSEP, record->file_name, record->file.index_line, str);
			return (FALSE);
		}
		str++;
		c = skip_spaces(&str);
		if (!verify_present_arg(record, elem, c))
			return (FALSE);
		while (*str && !ft_isspace(*str) && *str != SEPARATOR_CHAR)
			str++;
	}
	return (TRUE);
}

/*
********************************************************************************
********************************************************************************
*/

t_bool			verify_elem_str(t_record *record, t_elem *elem)
{
	int nb;

	if (!verify_args_separators(record, elem, elem->line))
		return (FALSE);
	nb = ft_nbr_words_charset(elem->line, ELEM_CHRST);
	if (nb < elem->op_case.nbr_arg)
	{
		ft_printf(MISSARG, record->file_name, record->file.index_line,\
			elem->op_case.shortcut, elem->op_case.nbr_arg, nb);
		return (FALSE);
	}
	else if (nb > elem->op_case.nbr_arg)
	{
		ft_printf(TOOMARG, record->file_name, record->file.index_line,\
			elem->op_case.shortcut, elem->op_case.nbr_arg, nb);
		return (FALSE);
	}
	if (!(elem->split = ft_split_charset(elem->line, ELEM_CHRST)))
	{
		ft_printf(ALLOC, record->file_name);
		exit(0);
	}
	return (verify_args_type(record, elem));
}
