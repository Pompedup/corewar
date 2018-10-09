/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ind.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 17:31:14 by abezanni          #+#    #+#             */
/*   Updated: 2018/10/09 18:31:48 by abezanni         ###   ########.fr       */
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
	size_t i;

	i = 0;
	while (str[i] && str[i] != ',' && str[i] != '#' && !ft_isspace(str[i]))
		i++;
	if (!i)
		exit(0);//gerer l'erreur
	(void)record;
	return (i);
}

t_bool	get_label_pos(t_record *record, t_elem *elem, t_arg *current_arg)
{
	char	*str;
	size_t	len;

	str = elem->line;
	str++;
	len = verif_syntax_label(record, str);
	get_label(record, current_arg, str, len);
	if (!current_arg->handled)
		elem->complete = FALSE;
	while (*str && *str != ',')
		str++;
}

t_bool	get_pos(t_record *record, t_elem *elem, t_arg *current_arg)
{
	char	*str;
	size_t	len;

	str = elem->line;
	len = nbr_len(str);
	if (ft_strnis(*str == '-' ? str + 1 : str, &ft_isdigit, *str == '-' ? len - 1 : len))
		current_arg->value = ft_atoi(str);
	str += ft_nbr_len(current_arg->value);
	current_arg->handled = TRUE;
	if (*str == '-')
		str++;
	while (ft_isdigit(*str))
		str++;
}

int				get_ind(t_record *record, t_arg *current_arg, t_elem *elem, int i)
{
	if (elem->line == ':')
		get_label_pos(record, elem, arg);
	else if (ft_isdigit(elem->line) || elem->line == '-')
		get_pos(record, elem, arg);
	else
		exit(0); //gerer l'erreur;
	if (*str && !ft_isspace(*str) && *str != ',')
		exit(0);
	current_arg->type = 4;
	current_arg->size = 2;
	elem->size += 2;
	elem->key += 3 << (6 - (2 * i));
	return (TRUE);
}
