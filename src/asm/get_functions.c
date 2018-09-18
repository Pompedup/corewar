/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 15:26:00 by abezanni          #+#    #+#             */
/*   Updated: 2018/09/18 16:20:28 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

extern t_op	g_op_tab[];

t_bool	is_correct_char(char c)
{
	return ((47 < c && c < 58) || 95 == c
		|| (96 < c && c < 123));
}

t_bool	is_correct_name(char *str)
{
	int i;
	i = 0;

	while (str[i] != ':')
	{
		if (!is_correct_char(str[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int		check_elem(char *str, t_elems **current_elem)
{
	int type;
	int key;

	type = 0;
	key = 0;
	(void)str;
	new_t_elem(current_elem, type, key);
	return (10);
}

char	*is_new_name(t_functions *functions, char *str, int end)
{
	while (functions)
	{
		if (!ft_strncmp(functions->name, str, end))
			return (NULL);
		functions = functions->next;
	}
	return (ft_strndup(str, end));
}

t_bool	get_name(t_functions *functions, char *str, char *label, char **name)
{
	int i;

	if ((i = label - str))
	{
		if (str[i] != ' ' && str[i - 1] != DIRECT_CHAR && str[i - 1] != SEPARATOR_CHAR)
		{
			if (is_correct_name(str))
			{
				*name = is_new_name(functions, str, i);
				return (TRUE);//ft_strndup(str, i);//j'ai un nom
			}
		}
	}
	return (FALSE);
}

char	*check_line(t_functions *functions, char *str, int *type)
{
	int		i;
	char	*label;
	char	*name;

	i = 0;
	name = NULL;
	str = search_begin(str);
	(void)type;
	(void)functions;//pour verifier si le nom existe deja
	if ((label = ft_strchr(str, LABEL_CHAR)))
		get_name(functions, str, label, &name);
	//while (g_op_tab[*type].shortcut)
	//{
	//	if (ft_strncmp(str + i, g_op_tab[*type].shortcut, ft_strlen(g_op_tab[*type].shortcut)))
	//		break;
	//	(*type)++;
	//}
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
		//ft_putendl((*current_line)->str);
		if ((name = check_line(record->functions, (*current_line)->str, &type)) || !(*current_function))
		{
			ft_putendl(name);
			current_function = new_t_function(current_function, name, pos);//si rien de cree ->erreur
			current_elem = &((*current_function)->elems);
		}
		if (g_op_tab[type].shortcut)
			pos += check_elem((*current_line)->str, current_elem);//si rien de cree ->erreur
		current_elem = &((*current_elem)->next);
		del_t_line(current_line);
	}
}
