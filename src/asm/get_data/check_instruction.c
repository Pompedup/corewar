/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_instruction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 14:27:56 by abezanni          #+#    #+#             */
/*   Updated: 2018/09/24 18:16:52 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

extern t_op	g_op_tab[];

int	is_label_char(int c)
{
	return ((47 < c && c < 58) || 95 == c
		|| (96 < c && c < 123));
}

static void	next_data(t_file *file)
{
	t_bool virgule;

	virgule = FALSE;
	while (*file->current == ' ' || *file->current == ',')
	{
		if (*file->current == ',')
		{
			if (!virgule)
				virgule = TRUE;
			else
				exit(0); //gerer l'erreur
		}
		file->current++;
	}
}

t_bool	check_authorized_arg(int type, int arg_type, int indice)
{
	if (!(g_op_tab[type].accept[indice] & arg_type))
	{
		exit(0);//gerer l'erreur
		return (FALSE);
	}
	return (TRUE);
}

int		verif_synrax(char *str)
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
	t_functions *functions;

	functions = record->functions;
	while (functions)
	{
		if (ft_strncmp(functions->name, str, len))
		{
			(void)current_arg;
			//position blablabla
			ft_printf("founded\n");
			current_arg->handled = TRUE;
			return ;
		}
		functions = functions->next;
	}
}

int		check_dir(t_record *record, t_arg *current_arg, char *str, int i)
{
	size_t len;

	(void)record; //pour les erreurs
	len = verif_synrax(str);
	str++;
	if (*str == ':')
	{
		get_label(record, current_arg, str, len);
		//it will be complique
	}
	else if (ft_isdigit(*str) || *str == '-' || *str == '+')
	{
		if (ft_strnis(*str == '-' ? str + 1 : str, &ft_isdigit, *str == '-' ? len - 1 : len))
			current_arg->value = ft_atoi(str);
	ft_printf("VALUE [%s] %d\n", str, current_arg->value);
	}
	else
		exit(0); //gerer l'erreur;
	str += ft_nbr_len(current_arg->value);
	if (*str && !ft_isspace(*str) && *str != ',')
		exit(0);
	current_arg->type = 2;
	return (2 << (6 - (2 * i)));
}

int		check_reg(t_record *record, t_arg *current_arg, char *str, int i)
{
	(void)record; //pour les erreurs
	str++;
	while (ft_isdigit(*str))
	{
		if ((current_arg->value = current_arg->value * 10 + (*str - 48)) > 99)
			exit(0);//expliquer l'erreur
		str++;
	}
	if (*str && !ft_isspace(*str) && *str != ',')
		exit(0);
	current_arg->type = 1;
	current_arg->handled = TRUE;
	return (1 << (6 - (2 * i)));
}

int		check_elem(t_record *record, t_file *file, t_elems **current_elem, int type)
{
	int		i;
	t_arg	**arg;

	i = 0;
	file->current = file->line + file->index_char;
	file->current = file->current + ft_strlen(g_op_tab[type].shortcut);
	next_data(file);
	new_t_elem(current_elem, type);
	arg = &((*current_elem)->args);
	while (i < g_op_tab[type].arg_authorized)
	{
		ft_putendl(file->current);
		if (*arg)
			arg = &((*arg)->next);
		new_t_arg(arg);
		if (*file->current == 'r' && check_authorized_arg(type, 1, i))
			(*current_elem)->key += check_reg(record, *arg, file->current, i);
		else if (*file->current == '%' && check_authorized_arg(type, 2, i))
			(*current_elem)->key += check_dir(record, *arg, file->current, i);
		else if (check_authorized_arg(type, 4, i))
			(*current_elem)->key += 3 << (6 - (2 * i));
		else
			exit(0);//gerer l'erreur
		if ((file->current = ft_strchr(file->current, ',')))
			next_data(file);
		i++;
	}
	ft_printf("%s\n", file->current);
	if (file->current || i < g_op_tab[type].arg_authorized)
		exit(0);//gerer l'erreur
	if (i == 1)
		(*current_elem)->key = 0;
	ft_printf("%x\n", (*current_elem)->key);
	return (10);
}
