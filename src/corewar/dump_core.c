/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_core.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecesari <ecesari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 14:29:45 by ccoupez           #+#    #+#             */
/*   Updated: 2018/11/01 14:27:38 by ecesari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
********************************************************************************
**	dump_no_color
********************************************************************************
*/

void	dump_no_color(t_corevm *vm)
{
	unsigned char	print[vm->octet_line_viz * 3 + 1];
	int				i;
	int				j;

	i = 0;
	j = 0;
	ft_bzero(print, vm->octet_line_viz * 3 + 1);
	ft_printf("0x0000 : ");
	while (i < MEM_SIZE)
	{
		print[j * 3] = HEXAMIN[((unsigned char *)vm->core)[i] / 16];
		print[j * 3 + 1] = HEXAMIN[((unsigned char *)vm->core)[i] % 16];
		print[j * 3 + 2] = ' ';
		j++;
		if (i && !((i + 1) % (vm->octet_line_viz)))
		{
			ft_printf("%.*s", j * 3 - 1, print);
			if (i + 1 < MEM_SIZE)
				ft_printf("\n%#.4x : ", i + 1);
			j = 0;
		}
		i++;
	}
	ft_putendl("");
}

/*
********************************************************************************
**	beginning_dump
********************************************************************************
*/

void	beginning_dump(t_corevm *vm)
{
	ft_printf("Voici l'arène au tour n°%d", vm->dump);
	if (vm->dump_color)
		ft_printf(", \e[4men couleur%s", COLOR_OFF);
	ft_printf(" et au format \e[4m%d%s octets par ligne.\n",\
	vm->octet_line_viz, COLOR_OFF);
	ft_printf("%s%s%s%s%s%s%s\n", LN_FL_64);
}

/*
********************************************************************************
**	dump_core
********************************************************************************
*/

void	dump_core(t_corevm *vm, int color)
{
	beginning_dump(vm);
	if (color)
		print_core(vm);
	else
		dump_no_color(vm);
	free_vm(vm);
	exit(0);
}
