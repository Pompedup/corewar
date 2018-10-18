/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   players_charged.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 13:36:25 by ccoupez           #+#    #+#             */
/*   Updated: 2018/10/18 14:54:43 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
********************************************************************************
**	players_charged_in_core transfers players into processes
**	i will be the index in core (relative position of every player in core)
**	place takes on values from 0 to nb->players
********************************************************************************
*/

void	players_charged_in_core(t_corevm *vm)
{
	int			i;
	int			j;
	float		place;
	t_player	*player;

	place = 0;
	player = vm->info->first_player;
	while (player)
	{
		i = ((place / (float)vm->info->nb_players) * (float)MEM_SIZE);
		create_process(vm, i, player);	
		j = -1;
		while (++j < player->len_process)
		{
			vm->core[i] = player->process[j];
			if (i != vm->info->first_processus->pc)
				vm->color[i] = vm->info->first_processus->color;
			else if (i == vm->info->first_processus->pc)
				vm->color[i] = vm->info->first_processus->color + 8;
			i++;
		}
		place += 1;
		player = player->next;
	}
	init_lives_player(vm);
}
