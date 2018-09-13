/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_corewar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 15:22:28 by ccoupez           #+#    #+#             */
/*   Updated: 2018/09/13 14:39:11 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		init_vm(char **av, t_corevm *vm)
{
	t_info	*info;

	vm->argv = av;
	vm->visu = 0;
	ft_bzero(vm->core, MEM_SIZE);
	vm->dump = 0;
	vm->nb_cycle = 0;
	vm->cycle_to_die = CYCLE_TO_DIE;
	vm->nb_lives = 0;
	vm->nb_max_live = NBR_LIVE;
	if (!(info = malloc(sizeof(t_info))))
		ft_error(vm, 9); //malloc error
	info->nb_players = 0;
	info->first_player = NULL;
	info->first_processus = NULL;
	vm->info = info;
}

/*
** la seule chose qui est malloc pour le moment
** cest les mailons de la liste chainee des joueurs
** et la structure info_player (1 int et lie a la liste chaine des joueurs)
*/
