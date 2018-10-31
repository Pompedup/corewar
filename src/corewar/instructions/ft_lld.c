/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lld.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecesari <ecesari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:44:04 by ccoupez           #+#    #+#             */
/*   Updated: 2018/10/29 19:09:25 by ecesari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
********************************************************************************
**	ft_lld
**	opcode 0x0d, changes carry
**  usage : lld ARG_1(ID/D4), ARG_2(RG)
**	same as load but without % IDX_MOD
**	loads the value of ARG_1 in ARG_2
********************************************************************************
*/

void		ft_lld(t_corevm *vm, t_process *process)
{
	int	*values;

	get_args(vm, process, g_op_tab[process->type_instruc[0]]);
	if (process->good_reg)
	{
		values = get_values(vm, process, 1, 1);
		if (values)
		{
			process->reg[process->args[1]] = values[0];
			process->carry = values[0] == 0 ? 1 : 0;
			free(values);
		}
	}
}
