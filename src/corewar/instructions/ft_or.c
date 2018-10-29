/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_or.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecesari <ecesari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:45:52 by ccoupez           #+#    #+#             */
/*   Updated: 2018/10/29 19:24:32 by ecesari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
********************************************************************************
**	ft_or
**	opcode 0x07, changes carry if the result is null
**  usage : or ARG_1(RG/ID/D4), ARG_2(RG/ID/D4), ARG_3(RG)
**	applies | (bitwise or) on ARG_1 | ARG_2 and stores the result in ARG_3 reg
********************************************************************************
*/

void	ft_or(t_corevm *vm, t_process *process)
{
	int	*values;

	get_args(vm, process, g_op_tab[process->type_instruc[0]]);
	if (process->good_reg)
	{
		values = get_values(vm, process, 3, 0);
		if (values)
		{
			process->reg[process->args[2]] = values[0] | values[1];
			process->carry = (process->reg[process->args[2]]) ? 0 : 1;
			free(values);
		}
	}
}
