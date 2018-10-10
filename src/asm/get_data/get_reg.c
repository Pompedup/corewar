/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_reg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 17:32:06 by abezanni          #+#    #+#             */
/*   Updated: 2018/10/10 14:02:52 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_bool	word_is_only_digit(t_record *record, t_elem *elem, t_arg *current_arg)
{
	int i;

	i = 1;
	while (ft_isdigit(elem->line[i]))
	{
		if (current_arg->value < 100)
			current_arg->value = current_arg->value * 10 + (elem->line[i] - 48);
		i++;
	}
	while (elem->line[i] && !ft_isspace(elem->line[i])\
		&& elem->line[i] != SEPARATOR_CHAR)
		i++;
	if (!ft_isdigit(elem->line[i - 1]) || current_arg->value > 99)
	{
		elem->line[i] = '\0';
		ft_printf(!ft_isdigit(elem->line[i - 1]) ? WRREG : BIGREG,\
			record->name_file, record->file.index_line, elem->line);
		return (FALSE);
	}
	elem->line += i;
	return (TRUE);
}

int		get_reg(t_record *record, t_arg *current_arg, t_elem *elem, int i)
{
	if (!word_is_only_digit(record, elem, current_arg))
		return (FALSE);
	while (ft_isspace(*elem->line))
		elem->line++;
	if (*elem->line && *elem->line != ',')
	{
		//second argument
		return (FALSE);
	}
	else if (*elem->line)
		elem->line++;
	current_arg->type = 1;
	current_arg->handled = TRUE;
	current_arg->size = 1;
	elem->size++;
	elem->key += 1 << (6 - (2 * i));
	return (TRUE);
}
