/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   players_charged.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 13:36:25 by ccoupez           #+#    #+#             */
/*   Updated: 2018/09/18 15:10:36 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** place les joueurs dans la memoire (l'arenne corewar)
** les champions sont chargés en mémoire de façon à espacer équitablement leurs points d’entrée.
** on a ca grace au calcul i = .. voir ci dessous
** et la on enregistre le 1er pc du joueur -> premiere case de la ou on a placé le programme du joueur
*/

void	players_charged_in_core(t_corevm *vm)
{
	int			i;
	int			j;
	float		place;
	t_player	*player;
	t_process	*process;

	player = vm->info->first_player;
	place = 0;
	while (player)
	{
		//printf("player->name_file %s \n", player->name_file);
		i = (place / (float)vm->info->nb_players * (float)MEM_SIZE);
		printf("player->num %d \n",player->num);
		process = create_process(vm, i, player);
		put_process_front(&(vm->info->first_processus), process);
		j = 0;
		while (j < player->len_process)
		{
			vm->core[i] = player->process[j];
			i++;
			j++;
		}
		place += 1;
		player = player->next;
	}



	//write(1, vm->core, MEM_SIZE);
	//ft_print_memory(vm->core, MEM_SIZE);
	process = vm->info->first_processus;
	while (process)
	{
		printf("process->reg[0] %d\n", process->reg[0]);
		printf("process->pc %d\n", process->pc);
		process = process->next;
	}
}
