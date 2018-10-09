/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 17:31:48 by abezanni          #+#    #+#             */
/*   Updated: 2018/10/09 18:30:37 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static size_t	nbr_len(char *str)
{
	size_t len;

	len = 0;
	if (*str == '-')
		str++;
	while (ft_isdigit(str[len]))
		len++;
	if (len == '0')
		exit(0);//gerer l'erreur && int min int max
	return (len);
}

static size_t	verif_syntax_label(t_record *record, char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != ',' && str[i] != '#' && !ft_isspace(str[i]))
		i++;
	if (!i)
		exit(0);//gerer l'erreur
	(void)record;
	return (i);
}

int		get_dir(t_record *record, t_arg *current_arg, t_elem *elem, int i)
{
	char	*str;
	size_t	len;

	str = elem->line;
	(void)record; //pour les erreurs
	str++;
	if (*str == ':')
	{
		str++;
		len = verif_syntax_label(record, str);
		get_label(record, current_arg, str, len);
		if (!current_arg->handled)
			elem->complete = FALSE;
		while (*str && *str != ',')
			str++;
	}
	else if (ft_isdigit(*str) || *str == '-')
	{
		len = nbr_len(str);
		if (ft_strnis(*str == '-' ? str + 1 : str, &ft_isdigit, *str == '-' ? len - 1 : len))
			current_arg->value = ft_atoi(str);
		current_arg->handled = TRUE;
		if (*str == '-')
			str++;
		while (ft_isdigit(*str))
			str++;
	}
	else
		exit(0); //gerer l'erreur; //erreur syntax
	if (*str && !ft_isspace(*str) && *str != ',')
	{
		exit(0);//gerer l'erreur
	}
	current_arg->type = 2;
	if (g_op_tab[elem->type].dir)
		current_arg->size = 2;
	else
		current_arg->size = 4;
	elem->size += current_arg->size;
	elem->key +=  2 << (6 - (2 * i));
	return (TRUE);
}
