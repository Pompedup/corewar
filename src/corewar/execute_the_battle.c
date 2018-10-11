/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_the_battle.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecesari <ecesari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 11:51:31 by ccoupez           #+#    #+#             */
/*   Updated: 2018/10/11 16:00:39 by ecesari          ###   ########.fr       */
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
**
********************************************************************************
*/

void	pc_color(t_corevm *vm, t_process *process)
{
	//redevenir normal
	if (vm->color[process->pc & (MEM_SIZE - 1)] < 12 && vm->color[process->pc & (MEM_SIZE - 1)] > 7)
		vm->color[process->pc & (MEM_SIZE - 1)] -= 8;
	else if (vm->color[process->pc & (MEM_SIZE - 1)] == 12)
		vm->color[process->pc & (MEM_SIZE - 1)]++;
	process->pc += process->pc_tmp;
	process->pc_tmp = 0;
	//devenir un pc
	if (vm->color[process->pc & (MEM_SIZE - 1)] < 8)
		vm->color[process->pc & (MEM_SIZE - 1)] = vm->color[process->pc & (MEM_SIZE - 1)] < 4 ? vm->color[process->pc & (MEM_SIZE - 1)] + 8 : vm->color[process->pc & (MEM_SIZE - 1)] + 4;//pour les cas de fork
	else if (vm->color[process->pc & (MEM_SIZE - 1)] == 13)
		vm->color[process->pc & (MEM_SIZE - 1)]--;
}

/*
********************************************************************************
** execute_the_battle get instructions for each alive player
** recupere les instructions de chaque process
********************************************************************************
*/

void	execute_the_battle(t_corevm *vm)
{
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
				manage_instruction(vm, process);//get_instructions.c
			}
			process = process->next;
		}

		vm->nbr_total_cycles++;

		if (vm->nbr_total_cycles > CYCLE_DEBUG)
			ft_printf("	nombre total de cycles vm->nbr_total_cycles %d\n", vm->nbr_total_cycles);
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
		// if (vm->nbr_total_cycles > CYCLE_DEBUG)
			// print_core(vm);
		if (vm->dump && vm->nbr_total_cycles == vm->dump)
		{
			print_core(vm);
			exit (0);//fonction qui free;
		}
		//tmp_cycle = check_max_checks(vm, tmp_cycle);
		//check_cycles(vm);
	}
}
