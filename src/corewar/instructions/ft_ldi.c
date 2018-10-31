/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecesari <ecesari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:41:15 by ccoupez           #+#    #+#             */
/*   Updated: 2018/10/29 17:25:23 by ecesari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
********************************************************************************
**	ft_ldi
**	opcode 0x0a, changes the carry
**  usage : ldi ARG_1(RG/ID/D2), ARG_2(ID/D2), ARG_3(RG)
**	reads REG_SIZE at the adress process->pc + (ARG_1 + ARG_2) and stores it
**	in ARG_3
********************************************************************************
*/

void	ft_ldi(t_corevm *vm, t_process *process)
{
	int	*values;
	int	add;

	get_args(vm, process, g_op_tab[process->type_instruc[0]]);
	if (process->good_reg)
	{
		values = get_values(vm, process, 3, 0);
		if (values)
		{
			add = ((values[0] + values[1]) % IDX_MOD) - IDX_MOD
				* ((((values[0] + values[1]) / IDX_MOD) & 1));
			process->reg[process->args[2]] = *((int *)(vm->core
				+ ((process->pc + add) & (MEM_SIZE - 1))));
			process->carry = (process->reg[process->args[2]]) ? 0 : 1;
			free(values);
		}
	}
}
