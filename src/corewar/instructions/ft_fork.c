/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecesari <ecesari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:40:03 by ccoupez           #+#    #+#             */
/*   Updated: 2018/10/29 16:58:57 by ecesari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
********************************************************************************
**	ft_fork
**	opcode 0x0c
**  usage : fork ARG_1(D2)
**	creates a new process to be placed at the adress (PC + (ARG_1 % IDX_MOD)
**	the new process inherits every state from the father
********************************************************************************
*/

void	ft_fork(t_corevm *vm, t_process *process)
{
	int			i;
	t_player	*tmp_player;
	t_process	*fork;

	tmp_player = vm->info->first_player;
	fork = NULL;
	get_two_octets(vm, process, 0);
	while (ft_strcmp(process->name, tmp_player->header->prog_name)
		&& tmp_player)
		tmp_player = tmp_player->next;
	if (tmp_player)
		fork = create_process(vm, ((process->pc + (process->args[0] % IDX_MOD))
			& (MEM_SIZE - 1)), tmp_player);
	i = 0;
	while (i < REG_NUMBER)
	{
		fork->reg[i] = process->reg[i];
		i++;
	}
	fork->carry = process->carry;
}
