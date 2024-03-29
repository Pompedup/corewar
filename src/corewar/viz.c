/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viz.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecesari <ecesari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 12:24:37 by ecesari           #+#    #+#             */
/*   Updated: 2018/11/01 13:41:59 by ecesari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
********************************************************************************
** count_processes returns the total number of processes
********************************************************************************
*/

int		count_processes(t_corevm *vm)
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
** print_header_viz displays the header of Corewar
********************************************************************************
*/

void	print_header_viz(t_corevm *vm)
{
	ft_printf("%s%s%s%s%s%s%s\n", LN_FL_64);
	ft_printf("\n%*s%s\n", (vm->octet_line_viz * 3 + 1) / 2, "",\
	"COREWAR");
}

/*
********************************************************************************
** print_introduction displays basic informations about the battle to occur
********************************************************************************
*/

void	print_introduction(t_corevm *vm)
{
	t_player	*player_to_introduce;
	int			padding_name;

	player_to_introduce = vm->info->first_player;
	ft_printf("%s%s%s%s%s%s%s\n", LN_FL_64);
	ft_printf("Nous avons le plaisir de vous présenter le combat entre ...\n");
	while (player_to_introduce)
	{
		if (player_to_introduce)
		{
			padding_name = vm->info->padding - player_to_introduce->precision;
			ft_printf(
"\t* le champion n°%d, nommé %s%d;%d;%dm%.*s%s%*s et pesant %d bytes (%.*s)\n",
ft_abs(player_to_introduce->num), COLOR_LET_ON, def_col(vm,\
player_to_introduce->color, 1), def_col(vm, player_to_introduce->color, 2),
def_col(vm, player_to_introduce->color, 3), player_to_introduce->precision,
player_to_introduce->header->prog_name, COLOR_OFF, padding_name, "",
player_to_introduce->header->prog_size, player_to_introduce->precision_c,
player_to_introduce->header->comment);
		}
		player_to_introduce = player_to_introduce->next;
	}
	ft_printf("%s%s%s%s%s%s%s\n", LN_FL_64);
}

/*
********************************************************************************
** print_summary displays the basic informations on the battle happening
** - current cycle
** - ongoing processes
** - champions (numbers and name)
** - cycle of last live OR cycle of death
** - number of lives for the current period (and percentages)
** - () period (number and beginning cycle)
** - constants (cycles_to_die, cycle_delta, nbr_live, max_checks)
********************************************************************************
*/

void	print_summary(t_corevm *vm)
{
	ft_printf("%s%s%s%s%s%s%s\n", LN_FL_64);
	ft_printf("\t\tCycle en cours\t:\t%d\t\t", vm->nbr_total_cycles);
	ft_printf("|\tNombre de process en cours\t:\t%d\n", count_processes(vm));
	display_name_champions(vm);
	display_statistics_alive_dead_champions(vm);
	display_statistics_last_cycle(vm);
	display_statistics_number_lives(vm);
	display_percentage_lives(vm);
	ft_printf("\nCONSTANTES");
	ft_printf("\tCYCLE_TO_DIE\t:\t%d\t\t", vm->cycle_to_die);
	ft_printf("|\tCYCLE DELTA\t:\t%d\t\t", CYCLE_DELTA);
	ft_printf("|\tNBR_LIVE\t:\t%d\t\t", NBR_LIVE);
	ft_printf("|\tMAX_CHECKS\t:\t%d\t\t\n", MAX_CHECKS);
	ft_printf("%s%s%s%s%s%s%s\n", LN_FL_64);
}

/*
********************************************************************************
** print_it_all call every function to correctly display our viz
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
