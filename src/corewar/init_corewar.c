/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_corewar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecesari <ecesari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 15:22:28 by ccoupez           #+#    #+#             */
/*   Updated: 2018/10/30 16:13:37 by ecesari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
********************************************************************************
**	init_lives_player
**	-	vm->lives_player[i][0] = process->num_player;
**	-	vm->lives_player[i][1] = number of lives made in one period
**	(since last decrease of CYCLE_TO_DIE);
**	-	vm->lives_player[i][2] = cycle of last live;
**	-	vm->lives_player[i][3] = linked to the processes;
********************************************************************************
*/

void	init_lives_player(t_corevm *vm)
{
	int			i;
	t_process	*process;

	i = 0;
	process = vm->info->first_processus;
	while (i < vm->info->nb_players && process)
	{
		vm->lives_player[i][0] = process->num_player;
		vm->lives_player[i][1] = 0;
		vm->lives_player[i][2] = 0;
		vm->lives_player[i][3] = 1;
		i++;
		process = process->next;
	}
}

/*
********************************************************************************
**	init_vm initializes every attributes of t_corevm *vm
**	- vm->color that will be used if vm->viz is activated,
**	set by default on GREY
**	- vm->argv
**	- vm->dump that is set at -1 to differientate it from 0
**	- vm->octet_line_viz that is the square of MEM_SIZE (i.e. 4096 then 64)
**	this ensure vm->viz to be a square (unless if dump is activated then 32)
**	- vm->cycle_to_die
**	- and mallocs vm->info
********************************************************************************
*/

void	init_vm(char **av, t_corevm **vm)
{
	int			i;
	static int	tab[] = {GREEN, PINK, BLUE, ORANGE, GREEN_S, PINK_S, BLUE_S,\
	ORANGE_S, GREEN_PC, PINK_PC, BLUE_PC, ORANGE_PC, GREY_PC, GREY};

	i = 0;
	if (!(*vm = ft_memalloc(sizeof(t_corevm))))
		ft_error(*vm, FAIL_MEMALLOC_00, 0);
	while (i < MEM_SIZE)
		(*vm)->color[i++] = 13;
	(*vm)->argv = av;
	(*vm)->dump = -1;
	(*vm)->octet_line_viz = 32;
	(*vm)->tab_color = tab;
	(*vm)->cycle_to_die = CYCLE_TO_DIE;
	if (!((*vm)->info = ft_memalloc(sizeof(t_info))))
		ft_error(*vm, FAIL_MEMALLOC_0, 0);
}
