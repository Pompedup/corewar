/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 15:26:00 by abezanni          #+#    #+#             */
/*   Updated: 2018/09/25 17:30:11 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

extern t_op	g_op_tab[];

char	*is_new_name(t_function *functions, char *str)
{
	while (functions)
	{
		if (!ft_strcmp(functions->name, str))
			return (NULL);
		functions = functions->next;
	}
	return (ft_strdup(str));
}

void	get_name(t_function *functions, char *str, char *label, char **name)
{
	int i;

	if ((i = label - str))
	{
		str[i] = '\0';
		if (ft_strisall(str, &is_label_char))
			*name = is_new_name(functions, str);
		str[i] = ':';
	}
}

static int	next_data(char *str)
{
	int i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	return (i);
}

t_bool	check_line(t_function *functions, t_file *file, int *type, char **name)
{
	int		i;
	char	*label;

	i = 0;
	*name = NULL;
	if ((label = ft_strchr(file->line + file->index_char, LABEL_CHAR)))
		get_name(functions, file->line + file->index_char, label, name);
	if (*name)
	{
		file->index_char += ft_strlen(*name) + 1;
		next_data(file->line + file->index_char);
	}
	while (g_op_tab[*type].shortcut)
	{
		if (!ft_strncmp(file->line + file->index_char, g_op_tab[*type].shortcut, ft_strlen(g_op_tab[*type].shortcut)))
			break;
		(*type)++;
	}
	if (*name)
		return (TRUE);
	return (FALSE);
}

void	get_function(t_record *record, t_file *file, t_function **current_function)
{
	t_elem		**current_elem;
	char		*name;
	int			type;
	int			addr;
	//rechercher si le debut n'est pas une erreur

	addr = 0;
	while (file->line)
	{
		type = 0;
		ft_putendl(file->line + file->index_char);
		if (check_line(record->functions, file, &type, &name) || !(*current_function))
		{
			current_function = new_t_function(current_function, name, addr);//si rien de cree ->erreur
			current_elem = &((*current_function)->elems);
		}
		if (g_op_tab[type].shortcut)
		{
			new_t_elem(current_elem, type, addr);
			addr += get_elem(record, file, *current_elem);//si rien de cree ->erreur
			current_elem = &((*current_elem)->next);
		}
		read_t_file(record, file);
	}
}
