/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_elem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 14:27:56 by abezanni          #+#    #+#             */
/*   Updated: 2018/10/03 17:23:43 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		is_label_char(int c)
{
	return ((47 < c && c < 58) || 95 == c
		|| (96 < c && c < 123));
}

void	next_comma(t_record *record, t_elem *elem)
{
	t_bool virgule;

	virgule = FALSE;
	(void)record;
	while (ft_isspace(*elem->line) || *elem->line == ',')
	{
		if (*elem->line == ',')
		{
			if (!virgule)
				virgule = TRUE;
			else
			{
				ft_putendl("impossible");
				exit(0); //gerer l'erreur
			}
		}
		elem->line++;
	}
}

t_bool	check_authorized_arg(t_record *record,
									t_elem *elem, int arg_type, int indice)
{
	if (!(g_op_tab[elem->type].accept[indice] & arg_type))
	{
		exit(0);//gerer l'erreur
		(void)record;
		return (FALSE);
	}
	return (TRUE);
}

int		verif_synrax(t_record *record, char *str)
{
	size_t	i;
	int		end;
	t_bool	space;

	space = FALSE;
	i = 0;
	end = -1;
	while (str[i] && str[i] != ',' && str[i] != '#')
	{
		if (ft_isspace(str[i]))
		{
			end = i - 1;
			if (space == TRUE)
				exit(0); // gerer l'erreur
				(void)record;
			space = TRUE;
		}
		i++;
	}
	if (end == -1)
		end = i - 1;
	return (end);
}

int		get_elem(t_record *record, t_file *file, t_elem *elem)
{
	int		i;
	t_arg	**arg;

	i = 0;
	elem->line = file->line + file->index_char;
	elem->line = elem->line + ft_strlen(g_op_tab[elem->type].shortcut);
	next_comma(record, elem);
	arg = &(elem->args);
	while (i < g_op_tab[elem->type].arg_authorized)
	{
		if (*arg)
			arg = &((*arg)->next);
		new_t_arg(arg, elem->addr);
		if (*elem->line == 'r' && check_authorized_arg(record, elem, 1, i))
			elem->key += get_reg(record, *arg, elem, i);
		else if (*elem->line == '%' && check_authorized_arg(record, elem, 2, i))
			elem->key += get_dir(record, *arg, elem, i);
		else if (check_authorized_arg(record, elem, 4, i))
			elem->key += get_ind(record, *arg, elem, i);
		if ((elem->line = ft_strchr(elem->line, ',')))
			next_comma(record, elem);
		i++;
	}
	if (elem->line || i < g_op_tab[elem->type].arg_authorized)
		exit(0);//gerer l'erreur
	if (i == 1)
		elem->key = 0;
	else
		elem->size++;
	return (elem->size);
}
