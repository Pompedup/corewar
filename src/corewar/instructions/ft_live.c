/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecesari <ecesari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:44:17 by ccoupez           #+#    #+#             */
/*   Updated: 2018/10/30 14:58:48 by ecesari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
********************************************************************************
**	ft_live
**	opcode 0x01
**  usage : live ARG_1(D4)
**	declares life for the number of 4 bytes following the opcode
**	we search for the right num_player
ft_printf("\n\ndans ft_live\n");
ft_printf("vm->lives_player[%d][0] %d\n", i, vm->lives_player[i][0]);
ft_printf("vm->lives_player[%d][1] %d\n", i, vm->lives_player[i][1]);
ft_printf("vm->lives_player[%d][2] %d\n", i, vm->lives_player[i][2]);
ft_printf("vm->lives_player[%d][3] %d\n", i, vm->lives_player[i][3]);
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
	if (i < vm->info->nb_players)
		vm->lives_player[i][3] = 1;
	i = 0;
	while (i < vm->info->nb_players
		&& process->args[0] != vm->lives_player[i][0])
		i++;
	if (i < vm->info->nb_players)
	{
		vm->lives_player[i][1]++;
		vm->lives_player[i][2] = vm->nbr_total_cycles;
		process->color_live = process->pc & (MEM_SIZE - 1);
	}
	vm->nb_lives++;
}
