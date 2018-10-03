/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_battle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecesari <ecesari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 11:08:35 by ccoupez           #+#    #+#             */
/*   Updated: 2018/10/03 14:59:18 by ecesari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** Tous les CYCLE_TO_DIE cycles, s'assurer que chaque processus a exécuté au
** moins un live depuis the last vérification sinon mise à mort. (Bonus bruitage !)
**
*/

int	check_live(t_corevm *vm)
{
	t_process *tmp;

	tmp = vm->info->first_processus;
	while (tmp)
	{
		if (tmp->live == 0)
		{
			tmp->live = -1;
			//commande a trouver pour faire le bruitage de la MORT
		}
		else if (tmp->live > 0)
			tmp->live = 0;
		tmp = tmp->next;
	}


	if (vm->nb_lives >= NBR_LIVE )
	{
		vm->cycle_to_die -= CYCLE_DELTA;
		return (1);
	}
	vm->nb_lives = 0;
	return (0);
}

/*
** -dump nbr_cycles Au bout de nbr_cycles cycles d’exécution,
** dump la mémoire sur la sortie standard, puis quitte la partie.
** La mémoire doit être dumpée au format hexadécimal, avec 32 octets par ligne.
*/

// void	check_cyles(t_corevm *vm)
// {
//
// }

/*
** Si on n’a pas décrémenté CYCLE_TO_DIE depuis MAX_CHECKS vérifications,
** on le décrémente
*/

// int		check_max_checks(t_corevm *vm, int tmp_cycle)
// {
// }
