/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_elem
.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 14:27:56 by abezanni          #+#    #+#             */
/*   Updated: 2018/09/25 17:22:27 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

extern t_op	g_op_tab[];

int	is_label_char(int c)
{
	return ((47 < c && c < 58) || 95 == c
		|| (96 < c && c < 123));
}

void	next_comma(t_record *record, t_elem
 *elem)
{
	t_bool virgule;

	virgule = FALSE;
	(void)record;
	while (*elem->line == ' ' || *elem->line == ',')
	{
		if (*elem->line == ',')
		{
			if (!virgule)
				virgule = TRUE;
			else
				exit(0); //gerer l'erreur
		}
		elem->line++;
	}
}

t_bool	check_authorized_arg(t_record *record, t_elem
 *elem, int arg_type, int indice)
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

void	get_label(t_record *record, t_arg *current_arg, char *str, size_t len)
{
	t_function *functions;

	functions = record->functions;
	ft_putendl("here");
	ft_putendl(str);
	while (functions)
	{
			ft_putendl(functions->name);
		if (!ft_strncmp(functions->name, str, len))
		{
			(void)current_arg;
			//position blablabla
			ft_printf("founded\n");
			current_arg->value = functions->addr - current_arg->addr;
			current_arg->handled = TRUE;
			return ;
		}
		functions = functions->next;
	}
	current_arg->copy = ft_strndup(str, len);
}

int		get_elem(t_record *record, t_file *file, t_elem
 *elem)
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
		ft_putendl(elem->line);
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
	ft_printf("%s\n", elem->line);
	if (elem->line || i < g_op_tab[elem->type].arg_authorized)
		exit(0);//gerer l'erreur
	if (i == 1)
		elem->key = 0;
	ft_printf("%x\n", elem->key);
	return (10);
}
