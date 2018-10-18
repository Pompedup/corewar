/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_the_battle.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 11:51:31 by ccoupez           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2018/10/18 15:14:37 by ecesari          ###   ########.fr       */
=======
/*   Updated: 2018/10/18 15:39:41 by ccoupez          ###   ########.fr       */
>>>>>>> 5d161b71d5d50f525ffdcef81598fc676f841930
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
********************************************************************************
** first if -> take off the old color of the pc
** second if -> put the new color for the pc
********************************************************************************
*/

void	pc_color(t_corevm *vm, t_process *process)
{
	if (vm->color[process->pc & (MEM_SIZE - 1)] < 12
		&& vm->color[process->pc & (MEM_SIZE - 1)] > 7)
		vm->color[process->pc & (MEM_SIZE - 1)] -= 8;
	else if (vm->color[process->pc & (MEM_SIZE - 1)] == 12)
		vm->color[process->pc & (MEM_SIZE - 1)]++;
	process->pc += process->pc_tmp;
	process->pc_tmp = 0;
	if (vm->color[process->pc & (MEM_SIZE - 1)] < 8)
		vm->color[process->pc & (MEM_SIZE - 1)] =\
			vm->color[process->pc & (MEM_SIZE - 1)] < 4 ?\
				vm->color[process->pc & (MEM_SIZE - 1)] + 8 :\
					vm->color[process->pc & (MEM_SIZE - 1)] + 4;
	else if (vm->color[process->pc & (MEM_SIZE - 1)] == 13)
		vm->color[process->pc & (MEM_SIZE - 1)]--;
}

void	who_still_lives(t_corevm *vm)
{
	int			i;
	t_process	*tmp;

	tmp = vm->info->first_processus;
	while (tmp)
	{
		i = 0;
		while (tmp->num_player != vm->lives_player[i][0]
		&& i < vm->info->nb_players)
			i++;
		if (tmp->num_player == vm->lives_player[i][0]
		&& !vm->lives_player[i][1] && !vm->lives_player[i][3])
		{
			tmp->live = -1;
			if (vm->color[tmp->pc & (MEM_SIZE - 1)] == 12)
				vm->color[tmp->pc & (MEM_SIZE - 1)]++;
			else if (vm->color[tmp->pc & (MEM_SIZE - 1)] > 7
				&& vm->color[tmp->pc & (MEM_SIZE - 1)] != 13)
				vm->color[tmp->pc & (MEM_SIZE - 1)] -= 8;
		}
		vm->lives_player[i][3] = 0;
		tmp = tmp->next;
	}
	i = 0;
	while (i < vm->info->nb_players)
		vm->lives_player[i++][1] = 0;
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
	if (vm->nb_lives == 0)
		return (-1);
	who_still_lives(vm);
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
	int			debug;

	debug = 0;
	cycle = 0;
	while ((cycle  = live_executed_in_one_cycle(vm, cycle)) > -1)
	{
		if (vm->dump != -1 && vm->nbr_total_cycles == vm->dump)
		{
			print_core(vm);
			exit (0);//fonction qui free;
		}

		process = vm->info->first_processus;
		// ft_printf("in %d\n", cycle);
		while (process)
		{
			if (process->live > -1)
				manage_instruction(vm, process);
			//ft_printf("%p - %p\n", process, process->next);
			//while (process == process->next);
			process = process->next;
		}
		// ft_printf("out %d\n", cycle);
		vm->nbr_total_cycles++;
		cycle++;
		if (vm->viz)
			print_core(vm);
		if (PRINTF)
		{
			if (vm->nbr_total_cycles > CYCLE_DEBUG + debug)
			{
				print_core(vm);
				ft_printf("-----------------------------------------------vm->nbr_total_cycles %d\n", vm->nbr_total_cycles);
				ft_printf("+++++++++++++++++++++++++++++++++++++++vm->cycle to die %d\n", vm->cycle_to_die);
				ft_printf("+++++++++++++++++++++++++++++++++++++++vm->nb_lives %d\n", vm->nb_lives);
				ft_printf("+++++++++++++++++++++++++++++++++++++++cycle %d\n", cycle);
				char *line;
				while (get_next_line(0, &line) == 0);
				if (*line == 'q')
					exit(0);
				debug += ft_atoi(line);
				free(line);
			}
		}
	}
	//if (PRINTF)
		ft_printf("total cycle %d\n", vm->nbr_total_cycles);
}
