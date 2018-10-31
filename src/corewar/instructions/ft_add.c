/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecesari <ecesari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:35:48 by ccoupez           #+#    #+#             */
/*   Updated: 2018/10/29 16:34:35 by ecesari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
********************************************************************************
**	ft_add
**	opcode 0x04, changes carry if the result is null
**	usage : add ARG_1(RG), ARG_2(RG), ARG_3(RG), key 54
**	adds the value in ARG_1 to the value in ARG_2 and puts it in ARG_3
********************************************************************************
*/

void	ft_add(t_corevm *vm, t_process *process)
{
	int	*values;

	get_args(vm, process, g_op_tab[process->type_instruc[0]]);
	if (process->good_reg)
	{
		values = get_values(vm, process, 3, 0);
		if (values)
		{
			process->reg[process->args[2]] = values[0] + values[1];
			process->carry = (process->reg[process->args[2]]) ? 0 : 1;
			free(values);
		}
	}
}
