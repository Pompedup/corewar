/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 14:29:29 by abezanni          #+#    #+#             */
/*   Updated: 2018/10/17 18:07:53 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static t_bool	is_present(t_record *record, t_arg *arg)
{
	if (ft_isspace(*(arg->copy + 1)) || *(arg->copy + 1) == SEPARATOR_CHAR)
	{
		ft_printf(REGNEED, record->file_name, record->file.index_line);
		return (FALSE);
	}
	return (TRUE);
}

t_bool			word_is_only_digit(t_record *record, t_arg *arg)
{
	int i;

	i = 1;
	while (ft_isdigit(arg->copy[i]))
	{
		if (arg->value <= REG_NUMBER)
			arg->value = arg->value * 10 + (arg->copy[i] - 48);
		i++;
	}
	if (!ft_isdigit(arg->copy[i - 1]) || arg->value > REG_NUMBER)
	{
		arg->copy[i] = '\0';
		ft_printf(!ft_isdigit(arg->copy[i - 1]) ? WRREG : BIGREG,\
			record->file_name, record->file.index_line, arg->copy);
		return (FALSE);
	}
	return (TRUE);
}

int				get_reg(t_record *record, t_elem *elem, t_arg *arg, int i)
{
	if (!is_present(record, arg))
		return (FALSE);
	if (!word_is_only_digit(record, arg))
		return (FALSE);
	arg->type = 1;
	arg->handled = TRUE;
	arg->size = 1;
	elem->size++;
	elem->key += 1 << (6 - (2 * i));
	return (TRUE);
}

int				get_ind(t_record *record, t_elem *elem, t_arg *arg, int i)
{
	if (!get_answer(record, elem, arg))
		return (FALSE);
	arg->type = 4;
	arg->size = 2;
	elem->size += 2;
	elem->key += 3 << (6 - (2 * i));
	return (TRUE);
}

int				get_dir(t_record *record, t_elem *elem, t_arg *arg, int i)
{
	arg->copy++;
	if (!get_answer(record, elem, arg))
		return (FALSE);
	arg->type = 2;
	if (g_op_tab[elem->type].dir)
		arg->size = 2;
	else
		arg->size = 4;
	elem->size += arg->size;
	elem->key += 2 << (6 - (2 * i));
	return (TRUE);
}
