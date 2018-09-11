/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_the_battle.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 11:51:31 by ccoupez           #+#    #+#             */
/*   Updated: 2018/09/11 17:04:19 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** recupere les instructions de chaque process
*/

void	execute_the_battle(t_corevm *vm)
{
	t_process	*process;
	//while (two_players_lives())
	//{
		process = vm->info->first_processus;
		while (process)
		{
			if (process->alive > -1)
			{
				check_instruction(vm, process);
				if (vm->nb_cycle >= vm->cycle_to_die)
					check_if_process_lives(process);
			}
			process = process->next;
		}
		//check_nb_live(vm);
		//check_nb_cycle(vm);
		if (vm->nb_cycle >= vm->cycle_to_die)
		{

		}
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
