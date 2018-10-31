/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_zjump.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecesari <ecesari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:33:22 by ccoupez           #+#    #+#             */
/*   Updated: 2018/10/29 19:41:41 by ecesari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
********************************************************************************
**	ft_zjmp
**	opcode 0x09
**  usage : zjmp ARG_1(D2)
**	if carry exists, jumps at the adress given in ARG_1
**	otherwise does nothing but uses the same amount of cycle
********************************************************************************
*/

void	ft_zjmp(t_corevm *vm, t_process *process)
{
	get_two_octets(vm, process, 0);
	if (!process->carry)
		return ;
	if (vm->color[process->pc & (MEM_SIZE - 1)] < 12
		&& vm->color[process->pc & (MEM_SIZE - 1)] > 7)
		vm->color[process->pc & (MEM_SIZE - 1)] -= 8;
	else if (vm->color[process->pc & (MEM_SIZE - 1)] == 12)
		vm->color[process->pc & (MEM_SIZE - 1)]++;
	process->pc += ((process->args[0]) % IDX_MOD);
	process->pc = process->pc & (MEM_SIZE - 1);
	process->pc_tmp = 0;
}
