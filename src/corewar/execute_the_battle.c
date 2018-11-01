/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_the_battle.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecesari <ecesari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 11:51:31 by ccoupez           #+#    #+#             */
/*   Updated: 2018/11/01 13:36:39 by ecesari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
********************************************************************************
**	declare_winner concludes corewar and declare the winner
**	the winner is the player that made the last live
********************************************************************************
*/

void	declare_winner(t_corevm *vm)
{
	int			i;
	int			last_live;
	t_player	*winner;

	last_live = 0;
	i = 0;
	while (i < vm->info->nb_players - 1)
	{
		if (vm->lives_player[i][2] < vm->lives_player[i + 1][2])
			last_live = i + 1;
		i++;
	}
	winner = vm->info->first_player;
	while (winner)
	{
		if (winner->num == vm->lives_player[last_live][0])
		{
			ft_printf("Le joueur %d (%s%d;%d;%dm%s%s) a gagné au tour n°%d\n",
(ft_abs(vm->lives_player[last_live][0])), COLOR_LET_ON, def_col(vm,\
winner->color, 1), def_col(vm, winner->color, 2), def_col(vm, winner->color,\
3), winner->header->prog_name, COLOR_OFF, vm->nbr_total_cycles);
			return ;
		}
		winner = winner->next;
	}
}

/*
********************************************************************************
** first if -> take off the old color of the pc
** second if -> put the new color for the pc
********************************************************************************
*/

void	pc_color(t_corevm *vm, t_process *process)
{
	if (vm->color[process->pc & (MEM_SIZE - 1)] < 12\
	&& vm->color[process->pc & (MEM_SIZE - 1)] > 7)
		vm->color[process->pc & (MEM_SIZE - 1)] -= 8;
	else if (vm->color[process->pc & (MEM_SIZE - 1)] == 12)
		vm->color[process->pc & (MEM_SIZE - 1)]++;
	process->pc += process->pc_tmp;
	process->pc_tmp = 0;
	if (vm->color[process->pc & (MEM_SIZE - 1)] < 8)
		vm->color[process->pc & (MEM_SIZE - 1)] =
			vm->color[process->pc & (MEM_SIZE - 1)] < 4 ?\
			vm->color[process->pc & (MEM_SIZE - 1)] + 8 :\
			vm->color[process->pc & (MEM_SIZE - 1)] + 4;
	else if (vm->color[process->pc & (MEM_SIZE - 1)] == 13)
		vm->color[process->pc & (MEM_SIZE - 1)]--;
}

/*
********************************************************************************
** live_executed_in_cycle check if live has been executed
********************************************************************************
*/

int		live_executed_in_one_cycle(t_corevm *vm, int cycle)
{
	static int	max_check = 0;
	int			i;

	if (cycle < vm->cycle_to_die)
		return (cycle);
	max_check++;
	if (vm->nb_lives == 0)
		return (-1);
	who_still_lives(vm);
	i = 0;
	while (i < vm->info->nb_players)
		vm->lives_player[i++][1] = 0;
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
	int			debug;
	t_process	*process;

	cycle = 0;
	debug = 0;
	while ((cycle = live_executed_in_one_cycle(vm, cycle)) > -1)
	{
		if (vm->dump != -1 && vm->nbr_total_cycles == vm->dump)
			dump_core(vm, vm->dump_color);
		process = vm->info->first_processus;
		while (process)
		{
			if (process->live > -1)
				manage_instruction(vm, process);
			process = process->next;
		}
		vm->nbr_total_cycles++;
		cycle++;
		if (vm->viz)
			print_it_all(vm);
		if (vm->viz_debug)
			viz_debug(vm, &debug);
	}
}
