/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 15:26:00 by abezanni          #+#    #+#             */
/*   Updated: 2018/09/03 23:05:39 by abezanni         ###   ########.fr       */
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

char	*check_name(char *str, char **type)
{
	int		i;
	char	*end;

	i = 0;
	while (g_op_tab[i].shortcut)
	{
		if ((*type = ft_strncmp(str, g_op_tab[i].shortcut, ft_strlen(g_op_tab[i].shortcut))))
			break;
		i++;
	}
	if (*type)
		return (NULL);
	if (!*type && (end = ft_strchr(str, LABEL_CHAR)))
		return (ft_strndup(str, end - str));//verifier s'il n'y a que des caractères autorisés
	return (NULL);
}

//95 97 - 122 48 - 57
void	get_functions(t_record *record, t_lines **current_line,
			t_functions **current_function)
{
	t_elems		**current_elem;
	char		*name;
	char		*type;
	int			pos;
	//rechercher si le debut n'est pas une erreur

	pos = 0;
	(void)record;
	while (*current_line)
	{
		if ((name = check_name((*current_line)->str, &type)) || !(*current_function))
		{
			ft_putendl(name);
			new_t_function(current_function, name, pos);//si rien de cree ->erreur
			current_elem = &((*current_function)->elems);
			current_function = &((*current_function)->next);
		}
		pos += check_elem((*current_line)->str, current_elem);//si rien de cree ->erreur
		current_elem = &((*current_elem)->next);
		del_t_line(current_line);
	}
}
