/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_the_battle.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 11:51:31 by ccoupez           #+#    #+#             */
/*   Updated: 2018/10/12 17:39:28 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

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
** live_executed_in_cycle check if live has been execute
********************************************************************************
*/

int		live_executed_in_one_cycle(t_corevm *vm, int cycle)
{
	static int	max_check = 0;

	if (cycle < vm->cycle_to_die)
		return (cycle);

	max_check++;
	if (vm->nb_lives > 0)
	{
		if (vm->nb_lives >= NBR_LIVE)
		{
			vm->cycle_to_die -= CYCLE_DELTA;
			max_check = 0;
		}
		else if (max_check == 10)
		{
			vm->cycle_to_die -= CYCLE_DELTA;
			max_check = 0;
		}
		vm->nb_lives = 0;
		return (0);
	}
	return (-1);
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
	t_process	*process;

	cycle = 0;
	while ((cycle  = live_executed_in_one_cycle(vm, cycle)) >= 0) // a revoir
	{
		if (vm->dump != -1 && vm->nbr_total_cycles == vm->dump)
		{
			print_core(vm);
			exit (0);//fonction qui free;
		}
			
			process = vm->info->first_processus;
			while (process)
			{
				// ft_printf(" dans execute process->pc %x\n", vm->core[process->pc & (MEM_SIZE -1)]);
				if (process->live > -1)
				{
					manage_instruction(vm, process);
				}
				process = process->next;
			}

		vm->nbr_total_cycles++;
		cycle++;
		ft_printf("---------------------------------------------------------------------vm->nbr_total_cycles %d\n", vm->nbr_total_cycles);
		//if (vm->nbr_total_cycles > CYCLE_DEBUG)
		//	print_core(vm);
		//	ft_printf("	nombre total de cycles vm->nbr_total_cycles %d\n", vm->nbr_total_cycles);
	}
	ft_printf("total cycle %d", vm->nbr_total_cycles);
}
