/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_the_battle.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecesari <ecesari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 11:51:31 by ccoupez           #+#    #+#             */
/*   Updated: 2018/10/02 15:51:00 by ecesari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
********************************************************************************
**
********************************************************************************
*/

int		two_players_lives(t_corevm *vm)
{
	int			nb;
	t_process	*process;

	nb = 0;
	process = vm->info->first_processus;
	while (process)
	{
		//ft_printf("process->live %d\n", process->live);
		if (process->live > -1)
			nb++;
		process = process->next;
	}
	if (nb > 0)
		{

		return (1);
		}
	return (0);
}

/*
********************************************************************************
** execute_the_battle get instructions for each alive player
** recupere les instructions de chaque process
********************************************************************************
*/

void	execute_the_battle(t_corevm *vm)
{
	//int i = 0;
	int			cycle;
	t_process	*process;

	cycle = 0;
	while (two_players_lives(vm))
	{
		process = vm->info->first_processus;
		while (process)
		{
			// ft_printf(" dans execute process->pc %x\n", vm->core[process->pc & (MEM_SIZE -1)]);
			if (process->live > -1)
			{
				// ft_printf(" process->pc %x\n", vm->core[process->pc & (MEM_SIZE -1)]);
				manage_instruction(vm, process);//get_instructions.c
				if (cycle >= vm->cycle_to_die)
					check_live(vm, process);//checking_the_battle.c
			}
			process = process->next;
		}
		if (vm->nb_lives >= vm->nb_max_live)
		{
			vm->cycle_to_die -= CYCLE_DELTA;
			vm->nb_lives = 0;
		}
		if (cycle > 15)
			return ;
		print_core(vm);
		//tmp_cycle = check_max_checks(vm, tmp_cycle);
		//check_cycles(vm);
		cycle++;
	}
}
