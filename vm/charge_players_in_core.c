/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   charge_players_in_core.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 15:52:38 by ccoupez           #+#    #+#             */
/*   Updated: 2018/07/20 16:04:06 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** place les joueurs dans la memoire (l'arenne corewar)
** il est demandé que : les champions sont chargés en mémoire de façon à espacer équitablement leurs
** points d’entrée.
** donc on a ca grace au calcul i = .. voir ci dessous
** et tout est caste en float sinon le calcul donne 0 tout le temps
*/

void	charge_players_in_core(t_corevm *vm)
{
	int			i;
	int			j;
	t_player	*player;

	player = vm->info_players->first;
	while (player)
	{
		printf("player->name_file %s \n", player->name_file);
		j = 0;
		i = ((float)player->num / (float)vm->info_players->nb_players
			* (float)MEM_SIZE);
		while (j < player->len_process)
		{
			vm->core[i] = player->process[j];
			i++;
			j++;
		}
		player = player->next;
	}
	print_memory(vm->core, MEM_SIZE);
}
