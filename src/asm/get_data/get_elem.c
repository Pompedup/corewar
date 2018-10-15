/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_elem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 14:27:56 by abezanni          #+#    #+#             */
/*   Updated: 2018/10/15 15:39:15 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		is_label_char(int c)
{
	return ((47 < c && c < 58) || 95 == c
		|| (96 < c && c < 123));
}

static t_bool	next_elem(t_record *record, t_elem *elem)
{
	while (ft_isspace(*elem->line))
		elem->line++;
	if (*elem->line == SEPARATOR_CHAR)
	{
		ft_printf(MISSBEF, record->file_name, elem->index_line, SEPARATOR_CHAR);
		return (FALSE);
	}
	return (TRUE);
}

static t_bool	check_authorized_arg(t_record *record,
									t_elem *elem, int arg_type, int indice)
{
	char *place;
	char *type;

	if (!(elem->op_case.accept[indice] & arg_type))
	{
		if (indice == 0)
			place = "first";
		else if (indice == 1)
			place = "second";
		else
			place = "third";
		if (arg_type == 1)
			type = S_REG;
		else if (arg_type == 2)
			type = S_DIR;
		else
			type = S_IND;
		ft_printf(WRARG, record->file_name, elem->index_line, type, place,\
			elem->op_case.shortcut);
		return (FALSE);
	}
	return (TRUE);
}

static t_bool	verify_exit_elem(t_record *record, t_file *file, t_elem *elem,\
																		int i)
{
	if ((elem->line && *elem->line) || i < elem->op_case.arg_authorized)
	{
		ft_printf(MISSARG, record->file_name, file->index_line,\
			elem->op_case.arg_authorized, i);
		return (FALSE);
	}
	if (i == 1)
		elem->key = 0;
	else
		elem->size++;
	record->tot += elem->size;
	return (TRUE);
}

//trop longue
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
	//gestion de la fin de ligne
	while (ft_isspace(*elem->line))
		elem->line++;
	if (*elem->line && *elem->line != SEPARATOR_CHAR)
	{
		if (i + 1 < elem->op_case.arg_authorized)
		{
			ending_str(elem->line);
			ft_printf(MISSSEP, record->file_name, record->file.index_line,\
				elem->line);
		}
		else
			ft_printf(TOOMUCH, record->file_name, record->file.index_line,\
				COMMENT_CHAR, elem->line);
		return (FALSE);
	}
	else if (*elem->line)
		elem->line++;
	if (!(next_elem(record, elem)))
		return (FALSE);
	return (TRUE);
}

t_bool			get_elem(t_record *record, t_file *file, t_elem *elem)
{
	int		i;
	t_arg	**arg;

	i = 0;
	if (!(next_elem(record, elem)))
		return (FALSE);
	arg = &(elem->args);
	while (i < elem->op_case.arg_authorized && *elem->line)
	{
		if (*arg)
			arg = &((*arg)->next);
		new_t_arg(arg, elem->addr);
		if (*elem->line == 'r')
			(*arg)->type = 1;
		else if (*elem->line == DIRECT_CHAR)
			(*arg)->type = 2;
		else if (int ou :)
			(*arg)->type = 4;
		if (!check_authorized_arg(record, elem, (*arg)->type, i))
			return (FALSE);
		if (!(get_value_arg(record, elem, *arg, i)))
			return (FALSE);
		i++;
	}
	return (verify_exit_elem(record, file, elem, i));
}
