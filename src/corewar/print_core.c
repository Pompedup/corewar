/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecesari <ecesari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 14:29:45 by ccoupez           #+#    #+#             */
/*   Updated: 2018/10/03 15:12:56 by ecesari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** La mémoire doit être dumpée au format hexadécimal, avec 32 octets par ligne.
*/

#define TEST 97

void	print_core(t_corevm *vm)
{
	char	*str;
	int		i;
	int		racine;
	char	print[TEST];

	i = 0;
	str = vm->core;
	racine = 32;
	print[TEST - 1] = '\n';
	while (i < MEM_SIZE)
	{
		print[(i % racine) * 3] = HEXAMIN[str[i] / 16];
		print[(i % racine) * 3 + 1] = HEXAMIN[str[i] % 16];
		print[(i % racine) * 3 + 2] = ' ';
		if (i && !(i % racine))
			write(1, print, TEST);
		i++;
	}
	ft_putendl("");
	ft_putendl("");
	ft_putendl("");











	//t_process	*process;

	//process = vm->info->first_processus;
	//comment en imprimant la core differencier les joueurs un peu partout
//	system("clear"); // pour pouvoir reecrire par dessus ᕙ༼*◕_◕*༽⊃━☆ﾟ.*･｡


	//ft_print_memory(vm->core, 30);
}
