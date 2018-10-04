/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecesari <ecesari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 14:29:45 by ccoupez           #+#    #+#             */
/*   Updated: 2018/10/04 18:23:31 by ecesari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		is_pc(t_corevm *vm)
{

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

	i = 0;
	j = 0;
	str = (unsigned char *)vm->core;
	racine = 64;//32ç
	print[TEST - 1] = '\n';
	while (i < MEM_SIZE)
	{
		if (i && !(i % racine))
		{
			write(1, print, j);
			j = 0;
		}
		print[(i % racine) * 3] = HEXAMIN[str[i] / 16];
		print[(i % racine) * 3 + 1] = HEXAMIN[str[i] % 16];
		print[(i % racine) * 3 + 2] = ' ';
		if (vm->color[i] != vm->color[i + 1])
		{
			write(1, print, j);
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
