/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_file_name.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 16:06:00 by abezanni          #+#    #+#             */
/*   Updated: 2018/10/20 20:09:34 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		is_label_char(int c)
{
	return ((47 < c && c < 58) || 95 == c
		|| (96 < c && c < 123));
}

t_bool	verif_file_name(t_record *record, char *str)
{
	char *end;

	if (!(end = ft_strendstr(str, ".s")))
	{
		ft_printf(WREXT, str, ".s");
		return (FALSE);
	}
	*end = '\0';
	record->final_name = ft_strjoin(str, ".cor");
	*end = '.';
	return (TRUE);
}
