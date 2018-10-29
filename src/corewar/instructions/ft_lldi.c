/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lldi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecesari <ecesari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:45:30 by ccoupez           #+#    #+#             */
/*   Updated: 2018/10/29 19:32:11 by ecesari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
********************************************************************************
**	ft_lldi
**	opcode 0x0a, changes the carry
**  usage : lldi ARG_1(RG/ID/D2), ARG_2(ID/D2), ARG_3(RG)
**	same as ldi but without % IDX_MOD
**	reads REG_SIZE at the adress process->pc + (ARG_1 + ARG_2) and stores it
**	in ARG_3
********************************************************************************
*/

void	ft_lldi(t_corevm *vm, t_process *process)
{
	int	*values;
	int	s;

	get_args(vm, process, g_op_tab[process->type_instruc[0]]);
	if (process->good_reg)
	{
		values = get_values(vm, process, 3, 1);
		if (values)
		{
			s = values[0] + values[1];
			process->reg[process->args[2]] = (char)(vm->core[((process->pc)
				+ s) & (MEM_SIZE - 1)]);
			process->carry = (process->reg[process->args[2]]) ? 0 : 1;
			free(values);
		}
	}
}
