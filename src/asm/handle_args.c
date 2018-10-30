/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:24:59 by abezanni          #+#    #+#             */
/*   Updated: 2018/10/30 18:44:12 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
********************************************************************************
********************************************************************************
*/

static void		print_option(t_record *record)
{
	ft_printf("\033[2J\033[HProgram size : %d bytes\n", record->tot);
	ft_printf("Name : %s\n", record->name);
	ft_printf("Comment : %s\n\n", record->comment);
	print_functions(record->functions);
}

/*
********************************************************************************
********************************************************************************
*/

void			handle_options(t_record *record, int options)
{
	if (options & 1)
		print_option(record);
	else
		write_file(record, record->functions);
}

/*
********************************************************************************
********************************************************************************
*/

static t_bool	get_options(char *str, int *options)
{
	char *c;

	while (*str)
	{
		if (!(c = ft_strchr(OPTIONS, *str)))
			return (FALSE);
		if (*c == 'a')
			*options = 1;
		str++;
	}
	return (TRUE);
}

/*
********************************************************************************
********************************************************************************
*/

t_bool			handle_args(int ac, char **av, int *options)
{
	int i;

	if (ac < 2)
	{
		ft_printf(USAGE);
		return (FALSE);
	}
	i = 1;
	*options = 0;
	while (i < ac)
	{
		if (*av[i] == '-')
		{
			if (!get_options(av[i] + 1, options))
				return (FALSE);
		}
		i++;
	}
	return (TRUE);
}
