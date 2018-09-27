/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 17:31:48 by abezanni          #+#    #+#             */
/*   Updated: 2018/09/27 17:27:56 by abezanni         ###   ########.fr       */
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

void	check_authorized_dir(t_record *record, t_elem *elem, int arg_type,\
			int indice)
{
	(void)arg_type;
	if (!(g_op_tab[elem->type].accept[indice] & T_DIR))
	{
		exit(0);//gerer l'erreur
		(void)record;
	}
}

int		get_dir(t_record *record, t_arg *current_arg, t_elem *elem, int i)
{
	ft_putendl("DIRECT");

	char *str;
	size_t len;

	str = elem->line;
	(void)record; //pour les erreurs
	str++;
	if (*str == ':')
	{
		str++;
		len = verif_syntax_label(record, str);
		get_label(record, current_arg, str, len);
		if (!current_arg->handled)
			elem->complete = FALSE;
		//it will be complique
		while (*str && *str != ',')
			str++;
		ft_printf("reste : %s\n", str);
	}
	else if (ft_isdigit(*str) || *str == '-')
	{
		len = nbr_len(str);
		if (ft_strnis(*str == '-' ? str + 1 : str, &ft_isdigit, *str == '-' ? len - 1 : len))
			current_arg->value = ft_atoi(str);
		ft_printf("VALUE [%s] %d\n", str, current_arg->value);
		current_arg->handled = TRUE;
		str += ft_nbr_len(current_arg->value);
	}
	else
		exit(0); //gerer l'erreur;
	ft_printf("%s\n", str);
	if (*str && !ft_isspace(*str) && *str != ',')
		exit(0);
	current_arg->type = 2;
	if (g_op_tab[elem->type].dir)
		current_arg->size = 2;
	else
		current_arg->size = 4;
	elem->size += current_arg->size;
	return (2 << (6 - (2 * i)));
}
