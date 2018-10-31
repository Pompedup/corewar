/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_label.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/26 12:54:55 by abezanni          #+#    #+#             */
/*   Updated: 2018/10/15 17:46:23 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	get_label(t_record *record, t_arg *current_arg, char *str, size_t len)
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
			}
		}
		functions = functions->next;
	}
}
