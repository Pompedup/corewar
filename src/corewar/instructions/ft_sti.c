/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecesari <ecesari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:29:56 by ccoupez           #+#    #+#             */
/*   Updated: 2018/10/29 19:37:36 by ecesari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
********************************************************************************
**	ft_sti
**	opcode 0x0b
**  usage : sti ARG_1(RG), ARG_2(RG/ID/D2), ARG_3(RG/D2)
**	copies ARG_1 at the address defined by ARG_2 + ARG_3
**	if ARG_2 or ARG_3 are registers, their values will be used as indexes
**	we change the color to highlight the result of st as the latest instruction
********************************************************************************
*/

void	ft_sti(t_corevm *vm, t_process *process)
{
	int	*values;
	int	add;
	int i;

	get_args(vm, process, g_op_tab[process->type_instruc[0]]);
	if (process->good_reg)
	{
		values = get_values(vm, process, 7, 0);
		if (values)
		{
			add = ((values[1] + values[2]) % IDX_MOD) - IDX_MOD
			* ((((values[1] + values[2]) / IDX_MOD) & 1));
			*(int *)(vm->core + ((process->pc + add) & (MEM_SIZE - 1))) =
				values[0];
			i = -1;
			while (++i < 4)
				vm->color[(process->pc + i + add) & (MEM_SIZE - 1)] =
					process->color + 4;
			free(values);
		}
	}
}
