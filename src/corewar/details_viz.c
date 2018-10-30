/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   details_viz.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecesari <ecesari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 12:24:37 by ecesari           #+#    #+#             */
/*   Updated: 2018/10/30 19:09:33 by ecesari          ###   ########.fr       */
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
	int			padding;

	ft_printf("Champions\t");
	player = vm->info->first_player;
	while (player)
	{
		padding = vm->info->padding - player->precision;
		// ft_printf("player->precision %d \n", player->precision);
		// ft_printf("vm->info->padding %d \n", vm->info->padding);
		// ft_printf("padding %d \n", padding);
		ft_printf("n°%d - %s%d;%d;%dm%.*s%s -%*s ",
		ft_abs(player->num), COLOR_LET_ON, def_col(vm, player->color, 1),
		def_col(vm, player->color, 2), def_col(vm, player->color, 3),
		player->precision, player->header->prog_name, COLOR_OFF, padding, "");
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
	int			padding;
	int 		i;

	// ft_printf("Champions");
	// ft_printf("         ");
		ft_printf("%*s", 16, "");
	player = vm->info->first_player;
	i = vm->info->nb_players - 1;
	while (i >= 0)
	{
		padding = vm->info->padding + 9;
		// ft_printf("player->precision %d \n", player->precision);
		// ft_printf("vm->info->padding %d \n", vm->info->padding);
		// ft_printf("padding %d \n", padding);
		if (vm->lives_player[i][3] == 0)
			ft_printf("%-*S", padding, L"☠️");
			// ft_printf("☠️");
		else
			ft_printf("%-*S", padding, L"🤗");
			// ft_printf("F");
		i--;
		// ft_printf("%*s", padding, "");
		// ft_printf("\t\t\t\t");
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
	float		total_lives_correct;
	int			percent;

	player = vm->info->first_player;
	total_lives_correct = 0;
	i = 0;
	while (i < vm->info->nb_players)
		total_lives_correct += vm->lives_player[i++][1];
	percent = 0;
	i = vm->info->nb_players - 1;
	while (i >= 0)
	{
		if (total_lives_correct)
			percent = (int)(((float)vm->lives_player[i][1] / total_lives_correct) * 100);
		ft_printf("\t\tpourcentage de vie sur total - %d%%-", percent);
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
