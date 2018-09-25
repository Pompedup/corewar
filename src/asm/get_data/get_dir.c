/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 17:31:48 by abezanni          #+#    #+#             */
/*   Updated: 2018/09/25 17:33:45 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		get_dir(t_record *record, t_arg *current_arg, t_elem *elem, int i)
{
	char *str;
	size_t len;

	str = elem->line;
	(void)record; //pour les erreurs
	len = verif_synrax(record, str);
	str++;
	if (*str == ':')
	{
		get_label(record, current_arg, str, len);
		//it will be complique
		while (*str && *str != ',')
			str++;
		ft_putendl(str);
	}
	else if (ft_isdigit(*str) || *str == '-')
	{
		if (ft_strnis(*str == '-' ? str + 1 : str, &ft_isdigit, *str == '-' ? len - 1 : len))
			current_arg->value = ft_atoi(str);
	ft_printf("VALUE [%s] %d\n", str, current_arg->value);
		current_arg->handled = TRUE;
	}
	else
		exit(0); //gerer l'erreur;
	str += ft_nbr_len(current_arg->value);
	if (*str && !ft_isspace(*str) && *str != ',')
		exit(0);
	current_arg->type = 2;
	return (2 << (6 - (2 * i)));
}
