/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecesari <ecesari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:44:17 by ccoupez           #+#    #+#             */
/*   Updated: 2018/10/26 12:52:43 by ecesari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
********************************************************************************
** live-> dit que je suis en vie
** 0x01
** suivie de 4 octets -> numero d'un joueur ou non
** Usage : live S(D4)
********************************************************************************
*/

void	ft_live(t_corevm *vm, t_process *process)
{
	int			i;

	process->live++;
	get_four_octets(vm, process, 0);
	i = 0;
	while (process->num_player != vm->lives_player[i][0])
		i++;
	vm->lives_player[i][3] = 1;
	i = 0;
	while (i < vm->info->nb_players
		&& process->args[0] != vm->lives_player[i][0])
		i++;
	if (i < vm->info->nb_players)
	{
		vm->lives_player[i][1]++;
		vm->lives_player[i][2] = vm->nbr_total_cycles;
		//ft_printf("vm->lives_player[i][2] %d\n", vm->lives_player[i][2]);
		process->color_live = process->pc & (MEM_SIZE - 1);
	}
	vm->nb_lives++;
/*
	ft_printf("\n\ndans ft_live\n");
	ft_printf("vm->lives_player[%d][0] %d\n", i, vm->lives_player[i][0]);
	ft_printf("vm->lives_player[%d][1] %d\n", i, vm->lives_player[i][1]);
	ft_printf("vm->lives_player[%d][2] %d\n", i, vm->lives_player[i][2]);
	ft_printf("vm->lives_player[%d][3] %d\n", i, vm->lives_player[i][3]);
*/
}
