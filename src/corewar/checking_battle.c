/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_battle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 11:08:35 by ccoupez           #+#    #+#             */
/*   Updated: 2018/09/11 17:04:21 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** je regarde si j'ai deja lu linstruction ou se situe mon pc
** si NON : je la recupere avec get_instruction
** si OUI : je regarde si on est arrive a la fin de son dernier cycle
** pour voir si on peut lexecuter ou non
*/

void	check_instruction(t_corevm *vm, t_process *process)
{

	if (process->type_instruc[0] == -1)
		get_instruction_type(vm, process);
	else
	{
		process->nb_cycle_instruc--;
		if (process->nb_cycle_instruc == 1)
			execute_instruction(vm, process);
	}
}

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
**
** Si pas décrémenté CYCLE_TO_DIE depuis MAX_CHECKS vérif on décrémente
**
*/

void	check_nb_live(t_corevm *vm)
{
	(void)vm;
	if (vm->nb_cycle >= MAX_CHECKS)
	{
		vm->cycle_to_die -= CYCLE_DELTA;
	}
	if (vm->nb_live >= vm->nb_max_live)
	{
		vm->cycle_to_die -= CYCLE_DELTA;
		vm->nb_live = 0;
	}

}


/*
** -dump nbr_cycles Au bout de nbr_cycles cycles d’exécution,
** dump la mémoire sur la sortie standard, puis quitte la partie.
** La mémoire doit être dumpée au format hexadécimal, avec 32 octets par ligne.
*/

void	check_nb_cycle(t_corevm *vm)
{
	(void)vm;
}
