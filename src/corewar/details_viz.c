/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   details_viz.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecesari <ecesari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 12:24:37 by ecesari           #+#    #+#             */
/*   Updated: 2018/10/30 15:04:39 by ecesari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
********************************************************************************
**
********************************************************************************
*/

void	display_evolution_cycle(t_corevm *vm)
{
	ft_printf("\t\tCycle en cours\t:\t%d\t\t", vm->nbr_total_cycles);
	ft_printf("|\tNombre de process en cours\t:\t%d\n", count_processes(vm));
}

/*
********************************************************************************
**
********************************************************************************
*/

void	display_name_champions(t_corevm *vm)
{
	t_player	*player;

	ft_printf("Champions");
	player = vm->info->first_player;
	while (player)
	{
		ft_printf("\tn°%d - %s%d;%d;%dm%s%s -\t",
		ft_abs(player->num), COLOR_LET_ON, def_col(vm, player->color, 1),
		def_col(vm, player->color, 2), def_col(vm, player->color, 3),
		player->header->prog_name, COLOR_OFF);
		ft_printf("\t\t\t");
		player = player->next;
	}
	ft_putendl("");
}

/*
********************************************************************************
**
********************************************************************************
*/

void	display_statistics_alive_dead_champions(t_corevm *vm)
{
	t_player	*player;
	int 		i;

	player = vm->info->first_player;
	i = vm->info->nb_players - 1;
	while (i >= 0)
	{
		ft_printf("\t");
		if (vm->lives_player[i][3] == 0)
			ft_printf("\t☠️");
		else
			ft_printf("\t🤗");
		i--;
		ft_printf("\t\t\t\t");
		player = player->next;
	}
	ft_putendl("");
}

/*
********************************************************************************
**
********************************************************************************
*/

void	display_statistics_last_cycle(t_corevm *vm)
{
	t_player	*player;
	int 		i;

	player = vm->info->first_player;
	i = vm->info->nb_players - 1;
	while (i >= 0)
	{
		// ft_printf("vm->lives_player[i][0] %d player->num %d\n", vm->lives_player[i][0], player->num);
		if (vm->lives_player[i][3] == 0)
			ft_printf("\t\tmort depuis le tour - %d -", vm->lives_player[i][2]);
		else
			ft_printf("\t\tdernière vie executée au tour - %d -",\
			vm->lives_player[i][2]);
		i--;
		player = player->next;
	}
	ft_putendl("");
}

/*
********************************************************************************
**
********************************************************************************
*/

void	display_statistics_number_lives(t_corevm *vm)
{
	t_player	*player;
	int 		i;

	player = vm->info->first_player;
	i = vm->info->nb_players - 1;
	while (i >= 0)
	{
		ft_printf("\t\tnombre de vies sur la période - %d -", vm->lives_player[i][1]);
		i--;
		player = player->next;
	}
	ft_putendl("");
}

/*
********************************************************************************
**
********************************************************************************
*/

void	display_percentage_lives(t_corevm *vm)
{
	t_player	*player;
	int 		i;

	player = vm->info->first_player;
	i = vm->info->nb_players - 1;
	while (i >= 0)
	{
		ft_printf("\t\tpourcentage de vie sur total - -", vm->lives_player[i][1]);
		i--;
		player = player->next;
	}
	ft_putendl("");
}

/*
********************************************************************************
**
********************************************************************************
*/

void	display_constants(t_corevm *vm)
{
	ft_printf("\nCONSTANTES");
	ft_printf("\tCYCLE_TO_DIE\t:\t%d\t\t", vm->cycle_to_die);
	ft_printf("|\tCYCLE DELTA\t:\t%d\t\t", CYCLE_DELTA);
	ft_printf("|\tNBR_LIVE\t:\t%d\t\t", NBR_LIVE);
	ft_printf("|\tMAX_CHECKS\t:\t%d\t\t\n", MAX_CHECKS);
	ft_printf("%s%s%s%s%s%s%s\n", LN_FL_64);
}
