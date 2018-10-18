/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:44:17 by ccoupez           #+#    #+#             */
/*   Updated: 2018/10/18 19:09:05 by ccoupez          ###   ########.fr       */
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
	while (process->args[0] != vm->lives_player[i][0]
		&& i < vm->info->nb_players)
		i++;
	if (process->args[0] == vm->lives_player[i][0])
	{
		vm->lives_player[i][1]++;
		vm->lives_player[i][2] = vm->nbr_total_cycles;
		process->color_live = process->pc & (MEM_SIZE - 1);
	}
	vm->nb_lives++;
}
