/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 15:26:00 by abezanni          #+#    #+#             */
/*   Updated: 2018/09/05 17:16:55 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

extern t_op	g_op_tab[];

int	check_elem(char *str, t_elems **current_elem)
{
	int type;
	int key;

	type = 0;
	key = 0;
	(void)str;
	new_t_elem(current_elem, type, key);
	return (10);
}

char	*is_new_name(char *name, int end, t_functions *functions)
{
	while (functions)
	{
		if (!ft_strncmp(functions->name, name, end))
			return (NULL);
		functions = functions->next;
	}

	return (ft_strndup(name, end));
}

char	*check_line(t_functions *functions, char *str, int *type)
{
	int		i;
	char	*label;
	char	*name;

	i = 0;
	name = NULL;
	str = search_begin(str);
	(void)functions;//pour verifier si le nom existe deja
	if ((label = ft_strchr(str, LABEL_CHAR)))
	{
		if ((i = label - str))
		{
			if (str[i - 1] != ' ' && str[i - 1] != DIRECT_CHAR && str[i - 1] != SEPARATOR_CHAR)
			{
				//95 97 - 122 48 - 57
				name = is_new_name(str, i, functions);//ft_strndup(str, i);//j'ai un nom
			}
		}
		else
			return (name);//la lign est mauvaise
	}
	while (g_op_tab[*type].shortcut)
	{
		if (ft_strncmp(str + i, g_op_tab[*type].shortcut, ft_strlen(g_op_tab[*type].shortcut)))
			break;
		(*type)++;
	}
	return (name);
}

void	get_functions(t_record *record, t_lines **current_line,
			t_functions **current_function)
{
	t_elems		**current_elem;
	char		*name;
	int			type;
	int			pos;
	//rechercher si le debut n'est pas une erreur

	pos = 0;
	(void)record;
	while (*current_line)
	{
		if ((name = check_line(record->functions, (*current_line)->str, &type)) || !(*current_function))
		{
			ft_putendl(name);
			current_function = new_t_function(current_function, name, pos);//si rien de cree ->erreur
			current_elem = &((*current_function)->elems);
		}
		if (g_op_tab[*type].shortcut)
			pos += check_elem((*current_line)->str, current_elem);//si rien de cree ->erreur
		current_elem = &((*current_elem)->next);
		del_t_line(current_line);
	}
}
