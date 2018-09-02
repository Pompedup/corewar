/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_corewar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 15:22:28 by ccoupez           #+#    #+#             */
/*   Updated: 2018/09/02 18:45:25 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		init_vm(char **av, t_corevm *vm)
{
	t_info_players	*players;

	vm->argv = av;
	vm->visu = 0;
	ft_bzero(vm->core, MEM_SIZE);
	vm->nb_total_cycles = 0;
	vm->dump = 0;
	vm->nb_live = 0;
	if (!(players = malloc(sizeof(t_info_players))))
		ft_error(vm, 9); //malloc error
	players->nb_players = 0;
	players->first_player = NULL;
	players->first_processus = NULL;
	vm->info_players = players;
}

/*
** la seule chose qui est malloc pour le moment
** cest les mailons de la liste chainee des joueurs
** et la structure info_player (1 int et lie a la liste chaine des joueurs)
*/
