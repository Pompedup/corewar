/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_battle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecesari <ecesari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 11:08:35 by ccoupez           #+#    #+#             */
/*   Updated: 2018/10/01 11:30:03 by ecesari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** A chaque exécution valide de l’instruction live, la machine doit afficher:
** "un processus dit que le joueur x(nom_champion) est en vie"
**
** Tous les CYCLE_TO_DIE cycles, s'assurer que chaque processus a exécuté au
** moins un live depuis the last vérification sinon mise à mort. (Bonus bruitage !)
**
*/

void	check_live(t_corevm *vm, t_process *process)
{
	(void)vm;
	if (process->live > 0)
	{
		process->live = 0; //toujours en vie mais passe a un autre cycle
	}
	else
		process->live = -1; //DEAD!!!
}

/*
** -dump nbr_cycles Au bout de nbr_cycles cycles d’exécution,
** dump la mémoire sur la sortie standard, puis quitte la partie.
** La mémoire doit être dumpée au format hexadécimal, avec 32 octets par ligne.
*/

void	check_cyles(t_corevm *vm)
{
	if (vm->nb_cycle >= vm->dump)
		ft_dump_exit(vm);
	if (vm->nb_cycle >= vm->cycle_to_die)
	{
			///
	}
}

/*
** Si on n’a pas décrémenté CYCLE_TO_DIE depuis MAX_CHECKS vérifications,
** on le décrémente
*/

int		check_max_checks(t_corevm *vm, int tmp_cycle)
{
	tmp_cycle++;
	if (tmp_cycle > MAX_CHECKS)
	{
		vm->cycle_to_die -= CYCLE_DELTA;
		tmp_cycle = 0;
	}
	return (tmp_cycle);
}
