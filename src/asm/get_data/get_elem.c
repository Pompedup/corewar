/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_elem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 14:27:56 by abezanni          #+#    #+#             */
/*   Updated: 2018/10/16 14:36:32 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"



static t_bool	get_value_arg(t_record *record, t_elem *elem, t_arg *arg, int i)
{
	if (arg->type == 1)
	{
		if (!get_reg(record, elem, arg, i))
			return (FALSE);
	}
	else if (arg->type == 2)
	{
		if (!get_dir(record, elem, arg, i))
			return (FALSE);
	}
	else if (arg->type == 4)
	{
		if (!get_ind(record, elem, arg, i))
			return (FALSE);
	}
	return (TRUE);
}






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

t_bool			verify_args_separators(t_record *record, t_elem *elem, char *str)
{
	char	c;

	c = skip_spaces(&str);
	if (!c || c == SEPARATOR_CHAR)
	{
		if (!c)
			ft_printf("ERROR%s\n", record->file_name);//!c ->no argument
		else
			ft_printf("ERROR%p\n", elem);//c	 ->missing argument
		return (FALSE);
	}
	while (*str && *str != SEPARATOR_CHAR)
		str++;
	while ((c = skip_spaces(&str)))
	{
		if (c != SEPARATOR_CHAR)
		{
			ft_printf("ERROR\n");//miss separator
			return (FALSE);
		}
		str++;
		c = skip_spaces(&str);
		if (!c || c == SEPARATOR_CHAR)
		{
			if (!c)
				ft_printf("ERROR\n");//miss arg
			else
				ft_printf("ERROR\n");//miss arg between
			return (FALSE);
		}
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

t_bool			get_elem(t_record *record, t_elem *elem)
{
	int		i;
	t_arg	**arg;

	if (!verify_elem_str(record, elem))
		return (FALSE);
	i = 0;
	arg = &(elem->args);
	while (i < elem->op_case.arg_authorized && *elem->line)
	{
		if (!(get_value_arg(record, elem, *arg, i)))
			return (FALSE);
		arg = &(*arg)->next;
		i++;
	}
	if (elem->op_case.arg_authorized > 1 || elem->op_case.id == 16)
		elem->size++;
	return (TRUE);
}
