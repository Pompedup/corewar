/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecesari <ecesari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 14:29:45 by ccoupez           #+#    #+#             */
/*   Updated: 2018/09/24 12:56:56 by ecesari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"



/*
** La mémoire doit être dumpée au format hexadécimal, avec 32 octets par ligne.
*/


void	print_core(t_corevm *vm)
{
	//t_process	*process;

	//process = vm->info->first_processus;
	//comment en imprimant la core differencier les joueurs un peu partout
//	system("clear"); // pour pouvoir reecrire par dessus ᕙ༼*◕_◕*༽⊃━☆ﾟ.*･｡


	ft_print_memory(vm->core, 30);
}
