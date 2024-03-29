/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   players_charged.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecesari <ecesari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 13:36:25 by ccoupez           #+#    #+#             */
/*   Updated: 2018/11/01 14:15:32 by ecesari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
********************************************************************************
** introducing_contestants displays basic information about the champions
********************************************************************************
*/

void	introducing_contestants(t_corevm *vm)
{
	t_player		*player_to_introduce;

	player_to_introduce = vm->info->first_player;
	ft_printf("%s%s%s%s%s%s%s\n", LN_FL_64);
	ft_printf("Nous avons le plaisir de vous présenter le combat entre ...\n");
	while (player_to_introduce)
	{
		ft_printf("\t* le champion n°%d, nommé %s%d;%d;%dm%s%s\
		et pesant %d bytes (%s)\n", ft_abs(player_to_introduce->num),
		COLOR_LET_ON, def_col(vm, player_to_introduce->color, 1),
		def_col(vm, player_to_introduce->color, 2),
		def_col(vm, player_to_introduce->color, 3),
		player_to_introduce->header->prog_name, COLOR_OFF,
		player_to_introduce->header->prog_size,
		player_to_introduce->header->comment);
		player_to_introduce->precision =
		lenght_display_string(player_to_introduce->header->prog_name,
		vm->info->padding);
		player_to_introduce->precision_c =
		lenght_display_string(player_to_introduce->header->comment,
		vm->info->padding);
		player_to_introduce = player_to_introduce->next;
	}
	ft_printf("%s%s%s%s%s%s%s\n", LN_FL_64);
}

/*
********************************************************************************
**	players_charged_in_core transfers players into processes
**	i will be the index in core (relative position of every player in core)
**	place takes on values from 0 to nb->players
**	init_lives_player defines the value for each line of the array
**	vm->info->padding helps define the largest amount of space available (185)
**	to display for champions (201 - "0x0000 : " = 192, - 9 spaces (n°x - - ))
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
		i = ((place++ / (float)vm->info->nb_players) * (float)MEM_SIZE);
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
		player = player->next;
	}
	init_lives_player(vm);
	vm->info->padding = (185 / vm->info->nb_players) - 9;
}
