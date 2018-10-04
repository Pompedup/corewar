/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_the_battle.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecesari <ecesari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 11:51:31 by ccoupez           #+#    #+#             */
/*   Updated: 2018/10/04 11:09:39 by ecesari          ###   ########.fr       */
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
	if (nb > 1)
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
	int			max_check;
	t_process	*process;

	cycle = 0;
	while (two_players_lives(vm) || vm->nb_cycles_to_die == 0) // a revoir
	{
		process = vm->info->first_processus;
		while (process)
		{
			// ft_printf(" dans execute process->pc %x\n", vm->core[process->pc & (MEM_SIZE -1)]);
			if (process->live > -1)
			{
				// ft_printf(" process->pc %x\n", vm->core[process->pc & (MEM_SIZE -1)]);
				if (vm->core[process->pc & (MEM_SIZE - 1)] == 0)
					process->pc++;
				else
					manage_instruction(vm, process);//get_instructions.c
			}
			process = process->next;
		}


		if (cycle == vm->cycle_to_die)
		{
			cycle = 0;
			vm->nb_cycles_to_die++;
			max_check = check_live(vm);
		}
		if (vm->nb_cycles_to_die % MAX_CHECKS == 0)
		{
			if (!max_check)
				vm->cycle_to_die -= CYCLE_DELTA;
			max_check = 0;
		}
		cycle++;
		if (cycle > 30)
			return ;
		print_core(vm);
		//tmp_cycle = check_max_checks(vm, tmp_cycle);
		//check_cycles(vm);
	}
}
