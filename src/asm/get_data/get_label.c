/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_label.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/26 12:54:55 by abezanni          #+#    #+#             */
/*   Updated: 2018/10/13 17:16:29 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
//retour non necessaire peut [etre]
t_bool	get_label(t_record *record, t_arg *current_arg, char *str, size_t len)
{
	t_function *functions;

	functions = record->functions;
	while (functions)
	{
		if (len == ft_strlen(functions->name))
		{
			if (!ft_strncmp(functions->name, str, len))
			{
				current_arg->value = functions->addr - current_arg->addr;
				current_arg->handled = TRUE;
				return (TRUE);
			}
		}
		functions = functions->next;
	}
	current_arg->copy = ft_strndup(str, len);
	return (FALSE);
}
