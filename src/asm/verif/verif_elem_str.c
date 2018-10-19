/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_elem_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 18:54:37 by abezanni          #+#    #+#             */
/*   Updated: 2018/10/18 18:55:11 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		is_label_char(int c)
{
	return ((47 < c && c < 58) || 95 == c
		|| (96 < c && c < 123));
}

t_bool			verify_args_type(t_record *record, t_elem *elem)
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
		if (*split[i] == 'r')
			(*arg)->type = 1;
		else if (*split[i] == '%')
			(*arg)->type = 2;
		else if (*split[i] == '-' || ft_isdigit(*split[i]) || *split[i] == ':')
			(*arg)->type = 4;
		else
		{
			//free + NULL args->copy
			ft_printf("Inconnu [%s]-%s\n", split[i], record->file_name);
			return (FALSE);
		}
		if (!(elem->op_case.accept[i] & (*arg)->type))
		{
			//free + NULL args->copy
			ft_printf("Incorrect\n");
			return (FALSE);
		}
		arg = &((*arg)->next);
		i++;
	}
	return (TRUE);
}

t_bool			verify_present_arg(t_record *record, t_elem *elem, char *str, char c)
{
	(void)str;
	if (!c || c == SEPARATOR_CHAR)
	{
		if (!c)
			ft_printf("ERROR%s\n", record->file_name);//!c ->no argument
		else
			ft_printf("ERROR%p\n", elem);//c	 ->missing argument (all or between ?)
		return (FALSE);
	}
	return (TRUE);
}

t_bool			verify_args_separators(t_record *record, t_elem *elem, char *str)
{
	char	c;

	c = skip_spaces(&str);
	if (!verify_present_arg(record, elem, str, c))
		return (FALSE);
	while (*str && !ft_isspace(*str) && *str != SEPARATOR_CHAR)
		str++;
	while ((c = skip_spaces(&str)))
	{
		if (c != SEPARATOR_CHAR)
		{
			ft_printf(MISSSEP, record->file_name, record->file.index_line, str);//miss separator
			return (FALSE);
		}
		str++;
		c = skip_spaces(&str);
		if (!verify_present_arg(record, elem, str, c))
			return (FALSE);
		while (*str && !ft_isspace(*str) && *str != SEPARATOR_CHAR)
			str++;
	}
	return (TRUE);
}

t_bool			verify_elem_str(t_record *record, t_elem *elem)
{
	int nb;

	if (!verify_args_separators(record, elem, elem->line))
		return (FALSE);
	nb = ft_nbr_words_charset(elem->line, ELEM_CHARSET);
	if (nb < elem->op_case.arg_authorized)
	{
		//pas assez d'arg
		return (FALSE);
	}
	else if (nb > elem->op_case.arg_authorized)
	{
		//trop d'arg
		return (FALSE);
	}
	if (!(elem->split = ft_split_charset(elem->line, ELEM_CHARSET)))
	{
		ft_printf(ALLOC, record->file_name);
		exit(0);
	}
	return (verify_args_type(record, elem));
}
