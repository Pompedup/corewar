/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecesari <ecesari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 14:29:45 by ccoupez           #+#    #+#             */
/*   Updated: 2018/10/22 18:35:03 by ecesari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
********************************************************************************
**
********************************************************************************
*/

int		color_live(t_corevm *vm, int i)
{
	int			color_live_on;
	t_process	*tmp;

	tmp = vm->info->first_processus;
	while (tmp)
	{
		if (tmp->color_live == i)
		{
			color_live_on = tmp->color;
			tmp->color_live = -1;
			return (color_live_on);
		}
		tmp = tmp->next;
	}
	return (-1);
}

/*
********************************************************************************
**
********************************************************************************
*/

void	put_color(t_corevm *vm, unsigned char *print, int j, int i)
{
	int			h;

	if (vm->color[i] > 7 && vm->color[i] < 13)
		ft_printf("\033[48;2;%d;%d;%dm\033[38;2;0;0;0m%.*s\033[0m"
		, (vm->tab_color[vm->color[i]] >> 16) & 0xff,
		(vm->tab_color[vm->color[i]] >> 8) & 0xff,
		(vm->tab_color[vm->color[i]]) & 0xff, j - 1, print);
	else
		ft_printf("\033[38;2;%d;%d;%dm%.*s\033[0m",
		(vm->tab_color[vm->color[i]] >> 16) & 0xff,
		(vm->tab_color[vm->color[i]] >> 8) & 0xff,
		(vm->tab_color[vm->color[i]]) & 0xff, j, print);
	if (i && !((i + 1) % (vm->octet_line_viz)) && i + 1 < MEM_SIZE)
		ft_printf("\n%#.4x : ", i + 1);
	else if (vm->color[i] > 7 && vm->color[i] < 13)
		ft_printf(" ");
	h = 0;
	while (h < j)
	{
		if (vm->color[i - j + h] > 3 && vm->color[i - j + h] < 8)
			vm->color[i - j + h] -= 4;
		h++;
	}
}

/*
********************************************************************************
**
********************************************************************************
*/

int		checking_color(t_corevm *vm,
unsigned char print[vm->octet_line_viz * 3 + 1], int i, int j)
{
	int			color;

	if (vm->color[i] != vm->color[i + 1]
		|| (i && !((i + 1) % (vm->octet_line_viz))))
	{
		put_color(vm, print, j * 3, i);
		j = 0;
	}
	else if ((color = color_live(vm, i)) > -1)
	{
		if (j > 1)
			put_color(vm, print, (j * 3 - 3), i);
		ft_printf("\033[48;2;%d;%d;%dm\033[38;1;255;255;255m%.*s\033[0m",
			(vm->tab_color[color] >> 16) & 0xff,
			(vm->tab_color[color] >> 8) & 0xff,
			(vm->tab_color[color]) & 0xff, 2, print + (j * 3 - 3));
		if (i && !((i + 1) % (vm->octet_line_viz)))
			ft_printf("\n");
		else
			ft_printf(" ");
		j = 0;
	}
	return (j);
}

/*
********************************************************************************
** print_core
********************************************************************************
*/

void	print_core(t_corevm *vm)
{
	unsigned char	print[vm->octet_line_viz * 3 + 1];
	int				i;
	int				j;

	i = 0;
	j = 0;
	// ft_printf("\E[H\E[2J");
	// ft_printf("\e[H\e[2J");
	ft_printf("\e[J\x1b[H");
	ft_printf("0x0000 : ");
	while (i < MEM_SIZE)
	{
		print[j * 3] = HEXAMIN[((unsigned char *)vm->core)[i] / 16];
		print[j * 3 + 1] = HEXAMIN[((unsigned char *)vm->core)[i] % 16];
		print[j * 3 + 2] = ' ';
		j++;
		j = checking_color(vm, print, i, j);
		i++;
	}
	ft_putendl("");
}

/*
********************************************************************************
** dump_core
********************************************************************************
*/

void	dump_core(t_corevm *vm, int color)
{
	unsigned char	print[vm->octet_line_viz * 3 + 1];
	int				i;
	int				j;

	i = 0;
	j = 0;
	ft_printf("0x0000 : ");
	while (i < MEM_SIZE)
	{
		print[j * 3] = HEXAMIN[((unsigned char *)vm->core)[i] / 16];
		print[j * 3 + 1] = HEXAMIN[((unsigned char *)vm->core)[i] % 16];
		print[j * 3 + 2] = ' ';
		j++;
		if (!color)
		{
			if (i && !((i + 1) % (vm->octet_line_viz)))
			{
				ft_printf("%.*s", j * 3 - 1, print);
				if (i + 1 < MEM_SIZE)
					ft_printf("\n%#.4x : ", i + 1);
				j = 0;
			}
		}
		else
			j = checking_color(vm, print, i, j);
		i++;
	}
	ft_putendl("");
	free_vm(vm);
	exit(0);
}
