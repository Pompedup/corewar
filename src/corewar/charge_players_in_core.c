/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   charge_players_in_core.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 15:52:38 by ccoupez           #+#    #+#             */
/*   Updated: 2018/09/02 18:45:06 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

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
	t_process	*process;

	player = vm->info_players->first_player;
	while (player)
	{
		//printf("player->name_file %s \n", player->name_file);
		j = 0;
		i = ((float)player->num / (float)vm->info_players->nb_players
			* (float)MEM_SIZE);
		process = create_process(vm, i, player->num, player->color);
		put_process_front(&(vm->info_players->first_processus), process);
		while (j < player->len_process)
		{
			vm->core[i] = player->process[j];
			i++;
			j++;
		}
		player = player->next;
	}



	//write(1, vm->core, MEM_SIZE);
	//print_memory(vm->core, MEM_SIZE);
	process = vm->info_players->first_processus;
	while (process)
	{
		printf("process->reg[0] %d\n", process->reg[0]);
		printf("process->pc %d\n", process->pc);
		process = process->next;
	}
}
