/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_name.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 18:32:18 by abezanni          #+#    #+#             */
/*   Updated: 2018/10/03 18:37:15 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static size_t	verif_syntax_label(t_record *record, char *str)
{
	size_t	i;

	i = 0;
	while (ft_strchr(LABEL_CHARS, str[i]))
		i++;
	//str[i] && str[i] != ',' && str[i] != '#' && !ft_isspace(str[i]))
	if (!i)
		(void)record;//bonne question
	return (i);
	(void)record;
}

t_bool	get_name()
{

	str++;
	if ((len = verif_syntax_label(record, str)) == -1)
		return (FALSE);
	get_label(record, current_arg, str, len);
	if (!current_arg->handled)
		elem->complete = FALSE;
	while (*str && *str != ',')
		str++;
}
