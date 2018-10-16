/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_the_battle.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 11:51:31 by ccoupez           #+#    #+#             */
/*   Updated: 2018/10/15 18:17:19 by ccoupez          ###   ########.fr       */
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

void	who_still_lives(t_corevm *vm, int lives_player[MAX_PLAYERS][2])
{
	int			i;
	t_process	*tmp;

	tmp = vm->info->first_processus;
	while (tmp)
	{
		i = 0;
		while (tmp->num_player != lives_player[i][0])
			i++;
		if (!lives_player[i][1])
		{
			tmp->live = -1;
			if (vm->color[tmp->pc & (MEM_SIZE - 1)] < 12 && vm->color[tmp->pc & (MEM_SIZE - 1)] > 7)
				vm->color[tmp->pc & (MEM_SIZE - 1)] -= 8;
		}
		tmp = tmp->next;
	}
}

/*
********************************************************************************
** live_executed_in_cycle check if live has been execute
********************************************************************************
*/

int		live_executed_in_one_cycle(t_corevm *vm, int cycle, int lives_player[MAX_PLAYERS][2])
{
	static int	max_check = 0;

	if (cycle < vm->cycle_to_die)
		return (cycle);

	max_check++;
	if (vm->nb_lives > 0)
	{
		ft_printf("-------------------fin dun cycle vm->nb_lives %d\n", vm->nb_lives);
		ft_printf("-------------------avant fin dun cycle vm->cycle_to_die %d\n", vm->cycle_to_die);
		who_still_lives(vm, lives_player);
		
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
		ft_printf("-------------------apres fin dun cycle vm->cycle_to_die %d\n", vm->cycle_to_die);
		return (0);
	}
	return (-1);
}

void	init_lives_player(t_corevm *vm, int lives_player[MAX_PLAYERS][2])
{
	int		i;
	t_process	*process;

	i = 0;
	process = vm->info->first_processus;
	while (i < vm->info->nb_players && process)
	{
		lives_player[i][0] = process->num_player;
		lives_player[i][1] = 0;
		i++;
		process = process->next;
	}
}

/*
********************************************************************************
** execute_the_battle get instructions for each alive player
** recupere les instructions de chaque process
********************************************************************************
*/

void	execute_the_battle(t_corevm *vm)
{
	int			i;
	int			cycle;
	t_process	*process;
	int			lives_player[MAX_PLAYERS][2];

	cycle = 0;
	init_lives_player(vm, lives_player);
	while ((cycle  = live_executed_in_one_cycle(vm, cycle, lives_player)) >= 0) // a revoir
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
					i = 0;
					while (lives_player[i][0] != process->num_player && i < vm->info->nb_players)
						i++;
					lives_player[i][1] += process->live;
					process->live = 0;
					manage_instruction(vm, process);

				}
				process = process->next;
			}

		vm->nbr_total_cycles++;
		cycle++;
		ft_printf("---------------------------------------------------------------------vm->nbr_total_cycles %d\n", vm->nbr_total_cycles);
		ft_printf("+++++++++++++++++++++++++++++++++++++++vm->nb_lives %d\n", vm->nb_lives);
		if (vm->nbr_total_cycles > CYCLE_DEBUG)
			print_core(vm);
		//	ft_printf("	nombre total de cycles vm->nbr_total_cycles %d\n", vm->nbr_total_cycles);
	}
	ft_printf("total cycle %d", vm->nbr_total_cycles);
}
