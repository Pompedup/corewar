/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_label.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/26 12:54:55 by abezanni          #+#    #+#             */
/*   Updated: 2018/09/27 15:01:55 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	get_label(t_record *record, t_arg *current_arg, char *str, size_t len)
{
	t_function *functions;

	functions = record->functions;
	ft_printf("[%s]%d\n", str, len);
	while (functions)
	{
		if (!ft_strncmp(functions->name, str, len))
		{
			current_arg->value = functions->addr - current_arg->addr;
			current_arg->handled = TRUE;
			return ;
		}
		functions = functions->next;
	}
	current_arg->copy = ft_strndup(str, len);
	ft_printf("arg->copy : %s", current_arg->copy);
}
