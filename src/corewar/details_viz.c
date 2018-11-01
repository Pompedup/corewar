/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   details_viz.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecesari <ecesari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 12:24:37 by ecesari           #+#    #+#             */
/*   Updated: 2018/11/01 12:40:20 by ecesari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

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
	int			i;

	ft_printf("%*s", 16, "");
	player = vm->info->first_player;
	i = vm->info->nb_players - 1;
	while (i >= 0)
	{
		padding = vm->info->padding + 12;
		if (vm->lives_player[i][3] == 0)
			ft_printf("%-*S", padding, L"☠️");
		else
			ft_printf("%-*S", padding, L"🤗");
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

void	display_statistics_last_cycle(t_corevm *vm)
{
	t_player	*player;
	int			padding;
	int			i;

	ft_printf("%*s", 16, "");
	player = vm->info->first_player;
	i = vm->info->nb_players - 1;
	while (i >= 0)
	{
		if (vm->lives_player[i][3] == 0)
		{
			padding = vm->info->padding + 9 - 25;
			ft_printf("mort depuis le tour - %d - %-*s",
			vm->lives_player[i][2], padding, "");
		}
		else
		{
			padding = vm->info->padding + 9 - 35;
			ft_printf("dernière vie executée au tour - %d - %-*s",\
			vm->lives_player[i][2], padding, "");
		}
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
	int			padding;
	int			i;

	ft_printf("%*s", 16, "");
	player = vm->info->first_player;
	i = vm->info->nb_players - 1;
	while (i >= 0)
	{
		padding = vm->info->padding + 9 - 35;
		ft_printf("nombre de vies sur la période - %d - %-*s",
		vm->lives_player[i][1], padding, "");
		i--;
		player = player->next;
	}
	ft_putendl("");
	ft_printf("%*s", 16, "");
}

/*
********************************************************************************
**
********************************************************************************
*/

void	display_percentage_lives(t_corevm *vm)
{
	t_player	*player;
	int			i;
	float		total_lives_correct;
	int			percent;
	int			padding;

	player = vm->info->first_player;
	total_lives_correct = 0;
	i = 0;
	while (i < vm->info->nb_players)
		total_lives_correct += vm->lives_player[i++][1];
	percent = 0;
	i = vm->info->nb_players - 1;
	while (i >= 0)
	{
		padding = vm->info->padding + 9 - 35;
		if (total_lives_correct)
			percent = (int)(((float)vm->lives_player[i][1]
			/ total_lives_correct) * 100);
		ft_printf("pourcentage de vie sur total - %d%% - %-*s",
		percent, padding, "");
		i--;
		player = player->next;
	}
	ft_putendl("");
}
