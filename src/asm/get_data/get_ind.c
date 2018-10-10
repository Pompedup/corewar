/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ind.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 17:31:14 by abezanni          #+#    #+#             */
/*   Updated: 2018/10/10 16:05:35 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static t_bool	nbr_len(char *str, size_t *len)
{
	*len = 0;
	if (*str == '-')
	{
		str++;
		*len = 1;
	}
	while (ft_isdigit(str[*len]))
		(*len)++;
	if (*len == 0)
	{
		exit(0);//gerer l'erreur && int min int max
		return (FALSE);
	}
	return (TRUE);
}

static size_t	verif_syntax_label(t_record *record, char *str, size_t *len)
{
	size_t i;

	*len = 0;
	while (str[*len] && str[*len] != SEPARATOR_CHAR && && !ft_isspace(str[*len]))
	{
		if (!(is_label_char(str[*len])))
		{
			return (FALSE);
		}
		(*len)++;
	}
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
	if (!(verif_syntax_label(record, elem->line + 1, &len)))
		return (FALSE);
	if (!(get_label(record, current_arg, elem->line + 1, len)))
		return (FALSE);
	if (!current_arg->handled)
		elem->complete = FALSE;
	while (*elem->line && *elem->line != ',')
		elem->line++;
	return (TRUE);
}

t_bool	get_pos(t_record *record, t_elem *elem, t_arg *current_arg)
{
	char	*str;
	size_t	len;

	str = elem->line;
	ft_strnbrlen(elem->line, &len);
	if (len == 1 && *elem->line == '-')
	{
		(void)record;//you try to trick me mother fucker
		return (FALSE);
	}
	if (elem->line[len] && !ft_isspace(elem->line[len]) && elem->line[len] != SEPARATOR_CHAR)
	{
		//TU SAIS PAS CE QUE C'EST UN CHIFFRE !?
		return (FALSE);
	}
	if (!ft_isint(elem->line, len))
	{
		//trop gros !!
		return (FALSE);
	}
	current_arg->value = ft_atoi(elem->line);
	if (!(nbr_len(elem->line, &len)))
		return (FALSE);
	elem->line += len;
	current_arg->handled = TRUE;
	return (TRUE);
}

int				get_ind(t_record *record, t_arg *current_arg, t_elem *elem, int i)
{
	if (*elem->line == ':')
		get_label_pos(record, elem, current_arg);
	else if (ft_isdigit(*elem->line) || *elem->line == '-')
		get_pos(record, elem, current_arg);
	else
		exit(0); //gerer l'erreur; %INTou %:label
	if (*elem->line && !ft_isspace(*elem->line) && *elem->line != ',')
		exit(0);

	//verifie la fin de l'argument
	while (ft_isspace(*elem->line))
		elem->line++;
	if (*elem->line && *elem->line != ',')
	{
		//second argument
		return (FALSE);
	}
	else if (*elem->line)
		elem->line++;
	current_arg->type = 4;
	current_arg->size = 2;
	elem->size += 2;
	elem->key += 3 << (6 - (2 * i));
	return (TRUE);
}
