/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_battle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 11:08:35 by ccoupez           #+#    #+#             */
/*   Updated: 2018/09/13 15:22:28 by ccoupez          ###   ########.fr       */
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

void	check_if_process_lives(t_process *process)
{
	if (process->alive > 0)
		process->alive = 0; //toujours en vie mais passe a un autre cycle
	else
		process->alive = -1; //DEAD!!!
}

/*
** S’il y a eu au moins NBR_LIVE exécutions de live depuis la dernière
** vérification, on décrémente CYCLE_TO_DIE de CYCLE_DELTA unités.
*/

void	check_nb_lives(t_corevm *vm)
{
	if (vm->nb_lives >= vm->nb_max_live)
	{
		vm->cycle_to_die -= CYCLE_DELTA;
		vm->nb_lives = 0;
	}
}

/*
** -dump nbr_cycles Au bout de nbr_cycles cycles d’exécution,
** dump la mémoire sur la sortie standard, puis quitte la partie.
** La mémoire doit être dumpée au format hexadécimal, avec 32 octets par ligne.
*/

void	check_scyles(t_corevm *vm)
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
