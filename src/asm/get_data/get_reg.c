/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_reg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 17:32:06 by abezanni          #+#    #+#             */
/*   Updated: 2018/09/25 17:34:55 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		get_reg(t_record *record, t_arg *current_arg, t_elem *elem, int i)
{
	char *str;

	str = elem->line;
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
