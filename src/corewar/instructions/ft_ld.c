/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecesari <ecesari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:39:08 by ccoupez           #+#    #+#             */
/*   Updated: 2018/10/29 17:07:14 by ecesari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
********************************************************************************
**	ft_ld
**	opcode 0x02, changes the carry if ARG_1 is null
**  usage : ld ARG_1(ID/D4), ARG_2(RG)
**	loads the value of ARG_1 in ARG_2
**	direct transfert from RAM to register
********************************************************************************
*/

void	ft_ld(t_corevm *vm, t_process *process)
{
	int	*values;

	get_args(vm, process, g_op_tab[process->type_instruc[0]]);
	if (process->good_reg)
	{
		values = get_values(vm, process, 1, 0);
		if (values)
		{
			process->reg[process->args[1]] = (int)values[0];
			process->carry = values[0] == 0 ? 1 : 0;
			free(values);
		}
	}
}
