/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_the_battle.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 11:51:31 by ccoupez           #+#    #+#             */
/*   Updated: 2018/09/28 13:17:14 by ccoupez          ###   ########.fr       */
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
		if (process->live == 0)
			nb++;
		process = process->next;
	}
	if (nb > 1)
		return (1);
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
	int			tmp_cycle;
	t_process	*process;

	tmp_cycle = 0;
	//while (two_players_lives(vm))
	//{
		process = vm->info->first_processus;
		while (process)
		{
			if (process->live > -1)
			{
				manage_instruction(vm, process);//get_instructions.c
				if (vm->nb_cycle >= vm->cycle_to_die)
					check_if_process_lives(vm, process);//checking_the_battle.c
			}
			process = process->next;
		}
		print_core(vm);
		//tmp_cycle = check_max_checks(vm, tmp_cycle);
		//check_cycles(vm);
		vm->nb_cycle++;
	//}
}



/*
	process = vm->info->first_processus;
	while (process)
	{
		printf("process->type_instruc[0] %d\n", process->type_instruc[0]);
		printf("process->type_instruc[1] %d\n", process->type_instruc[1]);
		printf("process->type_instruc[2] %d\n", process->type_instruc[2]);
		printf("process->type_instruc[3] %d\n", process->type_instruc[3]);
		printf("process->type_instruc[4] %d\n", process->type_instruc[4]);
		process = process->next;
	}
*/
