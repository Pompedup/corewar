/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viz.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecesari <ecesari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 12:24:37 by ecesari           #+#    #+#             */
/*   Updated: 2018/10/25 16:15:20 by ecesari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int	count_processes(t_corevm *vm)
{
	t_process	*process_to_count;
	int			count;

	count = 0;
	process_to_count = vm->info->first_processus;
	while (process_to_count)
	{
		count++;
		process_to_count = process_to_count->next;
	}
	return (count);
}

/*
********************************************************************************
** print_header_viz
********************************************************************************
*/

void	print_header_viz(t_corevm *vm)
{
	// if (vm->octet_line_viz == ft)
	// ft_printf("%*s%s\n", ft_sqrt(LN_FL_64_MEMSIZE), "_");
	ft_printf("%s%s%s%s%s%s%s\n", LN_FL_64);
	ft_printf("\n%*s%s\n", (vm->octet_line_viz * 3 + 1)/2, "", "COREWAR");
}

/*
********************************************************************************
** print_introduction
********************************************************************************
*/

void	print_introduction(t_corevm *vm)
{
	t_player		*player_to_introduce;

	player_to_introduce = vm->info->first_player;
	ft_printf("%s%s%s%s%s%s%s\n", LN_FL_64);
	ft_printf("Nous avons le plaisir de vous présenter le combat entre ...\n");
	while (player_to_introduce)
	{
		if (player_to_introduce)
		{
			ft_printf("	* le champion n°%d, nommé %s%d;%d;%dm%s%s\
			et pesant %d bytes (%s)\n",
			ft_abs(player_to_introduce->num), COLOR_LET_ON,
			def_col(vm, player_to_introduce->color, 1),
			def_col(vm, player_to_introduce->color, 2),
			def_col(vm, player_to_introduce->color, 3),
			player_to_introduce->header->prog_name, COLOR_OFF,
			player_to_introduce->header->prog_size,
			player_to_introduce->header->comment);
		}
		player_to_introduce = player_to_introduce->next;
	}
	ft_printf("%s%s%s%s%s%s%s\n", LN_FL_64);
}

/*
********************************************************************************
** print_summary
********************************************************************************
*/

void	print_summary(t_corevm *vm)
{
	t_player		*player;
	t_process		*process;

	ft_printf("%s%s%s%s%s%s%s\n", LN_FL_64);
	ft_printf("\t\tCycle en cours\t:\t%d\t\t", vm->nbr_total_cycles);
	ft_printf("|\tNombre de process en cours\t:\t%d\n", count_processes(vm));
	ft_printf("Champions");
	player = vm->info->first_player;
	while (player)
	{
		// if (player)
		// {
			ft_printf("\tn°%d - %s%d;%d;%dm%s%s -\t",
	ft_abs(player->num), COLOR_LET_ON,
	def_col(vm, player->color, 1), def_col(vm, player->color, 2),
	def_col(vm, player->color, 3), player->header->prog_name, COLOR_OFF);
	process = vm->info->first_processus;
		while (process)
		{
			if (process->num_player == player->num)
			{
				if (process->live == -1)
					ft_printf("☠️");
				else
					ft_printf("🤗");
			}
			process = process->next;
		}
			ft_printf("\t\t\t");
		player = player->next;
		}
	ft_putendl("");
	player = vm->info->first_player;
	while (player)
	{
		// if (player)
		// {
			ft_printf("\t\ttour de la derniere vie %d-\t", vm->lives_player[player->num][2]);
			// ft_printf("\t\tnombre de vie -\t\t\t");
		// }
		player = player->next;
	}

	ft_printf("\nCONSTANTES");
	ft_printf("\tCYCLE_TO_DIE\t:\t%d\t\t", vm->cycle_to_die);
	ft_printf("|\tCYCLE DELTA\t:\t%d\t\t", CYCLE_DELTA);
	ft_printf("|\tNBR_LIVE\t:\t%d\t\t", NBR_LIVE);
	ft_printf("|\tMAX_CHECKS\t:\t%d\t\t\n", MAX_CHECKS);
	ft_printf("%s%s%s%s%s%s%s\n", LN_FL_64);
}

/*
********************************************************************************
** print_it_all
********************************************************************************
*/

void	print_it_all(t_corevm *vm)
{
	ft_printf(CLEAR);
	print_header_viz(vm);
	print_introduction(vm);
	print_core(vm);
	print_summary(vm);
	usleep(100000);

}
