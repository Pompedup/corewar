/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 14:29:45 by ccoupez           #+#    #+#             */
/*   Updated: 2018/10/17 13:11:26 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
********************************************************************************
**
********************************************************************************
*/

void	put_color(t_corevm *vm, unsigned char *print, int j, int i)
{
	static int	tab[] = TAB_COLOR;


	//ft_printf("BUSSS ERROR\n");
	//ft_printf("vm->color[i] %d i %d\n", vm->color[i], i);

	if (vm->color[i] > 7 && vm->color[i] < 13)
	{
		ft_printf("\033[48;2;%d;%d;%dm\033[38;2;0;0;0m%.*s\033[0m", (tab[vm->color[i]] >> 16) & 0xff,(tab[vm->color[i]] >> 8) & 0xff,(tab[vm->color[i]]) & 0xff, j - 1, print);
		if (i && !((i + 1) % (vm->octet_line_viz)))
			ft_printf("\n%#.4x : ", i + 1);
		else
			ft_printf(" ");
	}
	else
	{
		ft_printf("\033[38;2;%d;%d;%dm%.*s\033[0m", (tab[vm->color[i]] >> 16) & 0xff,(tab[vm->color[i]] >> 8) & 0xff,(tab[vm->color[i]]) & 0xff, j, print);
		if (i && !((i + 1) % (vm->octet_line_viz)))
			ft_printf("\n%#.4x : ", i + 1);
	}
	// ft_printf(tmp, (tab[vm->color[i]] >> 16) & 0xff,(tab[vm->color[i]] >> 8) & 0xff,(tab[vm->color[i]]) & 0xff, print);
	int h = 0;
	while (h < j)
	{
		if (vm->color[i - j + h] > 3 && vm->color[i - j + h] < 13)
		if (vm->color[i - j  + h] < 8)
			vm->color[i - j+ h] -= 4;
		h++;
	}
	//	if (vm->color[i] > 3 && vm->color[i] < 13)
	//	if (vm->color[i] < 8)
	//		vm->color[i] -= 4;
	//
	// ft_printf("%s", print);
}

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
** print_core
**
** -------------------------- commentaire francais -----------------------------
** si dump nbr cycle => alors print core a nbr cycle au format 32 octets par ligne
** si !dump mais visualisateur alors visibilite de chaque cycle au format plus confortable de 64 octets par ligne
**	mais que faire si dump && visualisateur ? je propose 64 octet pour le visualisateur et 32 pour le dump (image finale)
**
** La mémoire doit être dumpée au format hexadécimal, avec 32 octets par ligne.
********************************************************************************
*/

void	print_core(t_corevm *vm)
{
	unsigned char	*str;
	unsigned char	print[vm->octet_line_viz * 3 + 1];
	static int		tab[] = TAB_COLOR;
	int				i;
	int				j;
	int				color;

	// ft_printf("print_core\n");
	i = 0;
	j = 0;
	str = (unsigned char *)vm->core;
	// print[TEST - 1] = '\n';
	ft_printf("\E[H\E[2J");
	ft_printf("0x0000 : ");
	while (i < MEM_SIZE)
	{
		// put_color(vm, print, j, i);
		print[j * 3] = HEXAMIN[str[i] / 16];
		print[j * 3 + 1] = HEXAMIN[str[i] % 16];
		print[j * 3 + 2] = ' ';
		j++;
		if (vm->color[i] != vm->color[i + 1] || (i && !((i + 1) % (vm->octet_line_viz))))
		{
			// if (i && !((i + 1) % (vm->octet_line_viz)))
			// {
			// 	print[j  * 3] = '\n';
			// 	put_color(vm, print, j * 3 + 1, i);
			// }
			// else
			put_color(vm, print, j * 3, i);
			//if (i && !((i + 1) % (vm->octet_line_viz)))
			//	ft_printf("\n");
				// put_color(vm, print, j * 3 - 1, i);
			 //write(1, print, j);
			//ft_bzero(print, TEST);
			j = 0;
		}
		//else if (i && !((i + 1) % (vm->octet_line_viz)))
		//{
		//	//print[j  * 3] = '\n';
		//	put_color(vm, print, j * 3, i);
		//	// ft_putnbrendl(i);
		//	 //write(1, print, j * 3);
		//	//ft_bzero(print, TEST);
		//	j = 0;
		//}
		if ((color = color_live(vm, i)) > -1)
		{
			if (j > 1)
				put_color(vm, print, (j * 3 - 3), i);
			ft_printf("\033[48;2;%d;%d;%dm\033[38;1;255;255;255m%.*s\033[0m", (tab[color] >> 16) & 0xff,(tab[color] >> 8) & 0xff,(tab[color]) & 0xff, 2, print + (j * 3 - 3));
			if (i && !((i + 1) % (vm->octet_line_viz)))
				ft_printf("\n");
			else
				ft_printf(" ");
			j = 0;
		}
		i++;
	}
	ft_putendl("");

	//t_process	*process;
	//process = vm->info->first_processus;
	//comment en imprimant la core differencier les joueurs un peu partout
	// system("clear"); // pour pouvoir reecrire par dessus ᕙ༼*◕_◕*༽⊃━☆ﾟ.*･｡
	// ft_print_memory(vm->core, MEM_SIZE);
}
