/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 14:29:45 by ccoupez           #+#    #+#             */
/*   Updated: 2018/10/09 14:01:39 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**
*/

void	put_color(t_corevm *vm, unsigned char *print, int j, int i)
{
	(void)vm;
	(void)j;
	(void)i;
	// (void)print;
	// int o;
	static int	tab[] = TAB_COLOR;
	// char		str[] = "\033[48;2;(tab[vm->color[i]] >> 16);(tab[vm->color[i]] >> 8) & 0xff;(tab[vm->color[i]]) & 0xffmprint\033[0m";
	// write(1, str, j * 3);
	// write(1, "\033[48;2;0xac;0xe5;0x80m;print\033[0m", j * 3);
	// o = tab[vm->color[i]];
// ft_printf("%x\n", vm->color[i]);

	// ft_printf("-----------i %d\n", i);
	// ft_printf("vm->color[i] %d\n", vm->color[i]);
	// ft_printf("tab[vm->color[i]]] %x\n", tab[vm->color[i]]);
	// ft_printf("(tab[vm->color[i]] >> 16) & 0xff %x\n", (tab[vm->color[i]] >> 16) & 0xff);
	// ft_printf("(tab[vm->color[i]] >> 16) & 0xff %x\n", (tab[vm->color[i]] >> 8) & 0xff);
	//
	// ft_printf("(tab[vm->color[i]] >> 16) & 0xff %x\n", (tab[vm->color[i]] >> 0) & 0xff);
//
	// char tmp[40];
//
	// ft_bzero(tmp, 40);
	// ft_strcat(tmp, "\033[38;2;%d;%d;%dm%.");
	// ft_strcat(tmp, "%.");
	// ft_strcat(tmp, ft_itoa(j));
	// ft_strcat(tmp, "s\033[0m");
	// ft_strcat(tmp, "s");
	// ft_putnbrendl(j);
	// ft_putendl(tmp);
	// ft_putendl(tmp);
	// ft_printf("\033[48;2;%d;%d;%dm%s\033[0m", 172,229,128, print);
	// ft_printf(tmp, print);
	if (vm->color[i] > 7 && vm->color[i] < 13)
	{
		ft_printf("\033[48;2;%d;%d;%dm\033[38;2;0;0;0m%.*s\033[0m", (tab[vm->color[i]] >> 16) & 0xff,(tab[vm->color[i]] >> 8) & 0xff,(tab[vm->color[i]]) & 0xff, j - 1, print);
		ft_printf(" ");
	}
	else
		ft_printf("\033[38;2;%d;%d;%dm%.*s\033[0m", (tab[vm->color[i]] >> 16) & 0xff,(tab[vm->color[i]] >> 8) & 0xff,(tab[vm->color[i]]) & 0xff, j, print);
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
** La mémoire doit être dumpée au format hexadécimal, avec 32 octets par ligne.
*/

#define TEST 193//97 pour 32

void	print_core(t_corevm *vm)
{

	unsigned char	*str;
	int				i;
	int				racine;
	unsigned char	print[TEST];
	int				j;

ft_printf("print_core\n");
	i = 0;
	j = 0;
	str = (unsigned char *)vm->core;
	racine = 64;//32
	// print[TEST - 1] = '\n';
sleep(1/5);
	ft_putendl("\E[H\E[2J");
	while (i < MEM_SIZE)
	{
		// put_color(vm, print, j, i);
		print[j * 3] = HEXAMIN[str[i] / 16];
		print[j * 3 + 1] = HEXAMIN[str[i] % 16];
		print[j * 3 + 2] = ' ';
		j++;
		if (vm->color[i] != vm->color[i + 1])
		{
			put_color(vm, print, j * 3, i);
			 //write(1, print, j);
			//ft_bzero(print, TEST);
			j = 0;
		}
		if (i && !((i + 1) % (racine)))
		{
			print[j  * 3] = '\n';
			put_color(vm, print, j * 3 + 1, i);
			// ft_putnbrendl(i);
			 //write(1, print, j * 3);
			//ft_bzero(print, TEST);
			j = 0;
		}
			// ft_printf("\x1B[A%s\x1B[K", print);
			// write(1, "\x1B[A", 1);
			// write(1, "\x1B[K", 1);
		i++;
	}
	ft_putendl("");


	//t_process	*process;

	//process = vm->info->first_processus;
	//comment en imprimant la core differencier les joueurs un peu partout
	// system("clear"); // pour pouvoir reecrire par dessus ᕙ༼*◕_◕*༽⊃━☆ﾟ.*･｡


	// ft_print_memory(vm->core, MEM_SIZE);
}
