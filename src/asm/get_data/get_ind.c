/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ind.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 17:31:14 by abezanni          #+#    #+#             */
/*   Updated: 2018/09/25 17:59:29 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	check_authorized_ind(t_record *record, t_elem *elem, int arg_type,\
			int indice)
{
	if (!(g_op_tab[elem->type].accept[indice] & T_IND))
	{
		exit(0);//gerer l'erreur
		(void)record;
	}
}

int		get_ind(t_record *record, t_arg *current_arg, t_elem *elem, int i)
{
	char *str;
	size_t len;
	(void)i;

		str = elem->line;
	(void)record; //pour les erreurs
	len = verif_synrax(record, str);
	if (*str == ':')
	{
		str++;
		get_label(record, current_arg, str, len);
		//it will be complique
		//str += ft_strlen(current_arg->copy);
		while (*str && *str != ',')
			str++;
		ft_putendl(str);
	}
	else if (ft_isdigit(*str) || *str == '-')
	{
		if (ft_strnis(*str == '-' ? str + 1 : str, &ft_isdigit, *str == '-' ? len - 1 : len))
			current_arg->value = ft_atoi(str);
		ft_printf("VALUE [%s] %d\n", str, current_arg->value);
		str += ft_nbr_len(current_arg->value);
		current_arg->handled = TRUE;
	}
	else
		exit(0); //gerer l'erreur;
	ft_putendl(str);
	if (*str && !ft_isspace(*str) && *str != ',')
		exit(0);
	current_arg->type = 4;
	return (3 << (6 - (2 * i)));
}
