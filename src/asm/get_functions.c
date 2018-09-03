/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 15:26:00 by abezanni          #+#    #+#             */
/*   Updated: 2018/09/03 19:06:34 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	check_elem(char *str, t_elems **current_elem)
{
	int type;
	int key;

	type = 0;
	key = 0;
	(void)str;
	new_t_elem(current_elem, type, key);
}

char	*check_name(char *str)
{
	char	*name;
	int		size;

	return (str);
}

char	*correct_line(char *str)
{
	extern t_op	g_op_tab;
	char		*result;

	while (g_op[i]->)
	{
		if ((result = ft_strstr(str, g_op[i]->shortcut)))
			return (result);
	}
	return (NULL);
}

void	get_functions(t_record *record)
{
	t_lines		**current_line;
	t_elems		**current_elem;
	t_functions	**current_function;
	char		*name;
	int			pos;
	//rechercher si le debut n'est pas une erreur

	current_line = &(record->lines);
	current_function = &(record->functions);
	pos = 0;
	while (*current_line)
	{
		name = correct_line((*current_line)->str);
		if ((name = check_name((*current_line)->str, name)) || !(*current_function))
		{
			new_t_function(current_function, name, pos);//si rien de cree ->erreur
			current_elem = &((*current_function)->elems);
		}
		check_elem((*current_line)->str, current_elem);//si rien de cree ->erreur
		del_t_line(current_line);
	}
}
