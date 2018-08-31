/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   charge_players_in_core.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 15:52:38 by ccoupez           #+#    #+#             */
/*   Updated: 2018/08/31 15:55:35 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** place les joueurs dans la memoire (l'arenne corewar)
** les champions sont chargés en mémoire de façon à espacer équitablement leurs points d’entrée.
** on a ca grace au calcul i = .. voir ci dessous
** et la on enregistre le 1er pc du joueur -> premiere case de la ou on a placé le programme du joueur*/

void	charge_players_in_core(t_corevm *vm)
{
	int			i;
	int			j;
	t_player	*player;

	player = vm->info_players->first_player;
	while (player)
	{
		//printf("player->name_file %s \n", player->name_file);
		j = 0;
		i = ((float)player->num / (float)vm->info_players->nb_players
			* (float)MEM_SIZE);
		//		process = create_processus(vm, &(vm->core[i]), player);
		//put_process_first(process);
		//printf("player->pc %p\n", player->pc);
		//player->pc = &(vm->core[i]);
		//printf("player->pc %p\n", player->pc);
		while (j < player->len_process)
		{
			vm->core[i] = player->process[j];
			i++;
			j++;
		}
		player = player->next;
	}
	//write(1, vm->core, MEM_SIZE);
	print_memory(vm->core, MEM_SIZE);
}
