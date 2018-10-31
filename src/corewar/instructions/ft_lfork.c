/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lfork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecesari <ecesari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:40:58 by ccoupez           #+#    #+#             */
/*   Updated: 2018/10/29 17:26:36 by ecesari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
********************************************************************************
**	ft_lfork
**	opcode 0x0f
**  usage : lfork ARG_1(D2)
**	same as fork but without % IDX_MOD
**	creates a new process to be placed at the adress (PC + (ARG_1)
**	the new process inherits every state from the father
********************************************************************************
*/

void	ft_lfork(t_corevm *vm, t_process *process)
{
	int			i;
	t_player	*tmp;
	t_process	*fork;

	tmp = vm->info->first_player;
	fork = NULL;
	get_two_octets(vm, process, 0);
	while (ft_strcmp(process->name, tmp->header->prog_name) && tmp)
		tmp = tmp->next;
	if (tmp)
		fork = create_process(vm, ((process->pc + process->args[0])
			& (MEM_SIZE - 1)), tmp);
	i = 0;
	while (i < REG_NUMBER)
	{
		fork->reg[i] = process->reg[i];
		i++;
	}
	fork->carry = process->carry;
}
