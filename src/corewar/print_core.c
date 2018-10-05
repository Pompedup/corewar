/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecesari <ecesari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 14:29:45 by ccoupez           #+#    #+#             */
/*   Updated: 2018/10/05 15:25:31 by ecesari          ###   ########.fr       */
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
	(void)print;
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
	// ft_printf("(tab[vm->color[i]] >> 16) & 0xff %x\n", (tab[vm->color[i]] >> 0) & 0xff);
//

//	ft_putstr(ROB);
	// ft_putstr(tab[vm->color[i]]);
	// ft_putstr(print);
	// ft_putendl("fun");
	// ft_putstr(ROB_FIN);
	// ft_printf("\033[48;2;%d;%d;%dm%s\033[0m", 172,229,128, print);
	ft_printf("\033[38;2;%d;%d;%dm%s\033[0m", (tab[vm->color[i]] >> 16) & 0xff,(tab[vm->color[i]] >> 8) & 0xff,(tab[vm->color[i]]) & 0xff, print);
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
	while (i < MEM_SIZE)
	{
			put_color(vm, print, j, i);
		if (i && !(i % racine))
		{
			print[j *3] = '\n';
			put_color(vm, print, j, i);
			// write(1, print, j * 3);
			j = 0;
		}
		print[(i % racine) * 3] = HEXAMIN[str[i] / 16];
		print[(i % racine) * 3 + 1] = HEXAMIN[str[i] % 16];
		print[(i % racine) * 3 + 2] = ' ';
		if (vm->color[i] != vm->color[i + 1])
		{
			put_color(vm, print, j, i);
			// write(1, print, j);
			j = 0;
		}
			// ft_printf("\x1B[A%s\x1B[K", print);
			// write(1, "\x1B[A", 1);
			// write(1, "\x1B[K", 1);
		i++;
		j++;
	}
	ft_putendl("");



	//t_process	*process;

	//process = vm->info->first_processus;
	//comment en imprimant la core differencier les joueurs un peu partout
	// system("clear"); // pour pouvoir reecrire par dessus ᕙ༼*◕_◕*༽⊃━☆ﾟ.*･｡


	// ft_print_memory(vm->core, MEM_SIZE);
}
