/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecesari <ecesari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 11:07:13 by ccoupez           #+#    #+#             */
/*   Updated: 2018/10/29 19:29:08 by ecesari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
********************************************************************************
**	ft_st
**	opcode 0x03
**  usage : st ARG_1(RG), ARG_2(RG/ID)
**	stores ARG_1 in reg ARG_2 or at ind ARG_2
**	we change the color to highlight the result of st as the latest instruction
********************************************************************************
*/

void	ft_st(t_corevm *vm, t_process *process)
{
	int	*values;
	int	add;
	int i;

	get_args(vm, process, g_op_tab[process->type_instruc[0]]);
	if (!process->good_reg)
		return ;
	values = get_values(vm, process, 1, 0);
	ft_memrev(&values[0], 4);
	if (!values)
		return ;
	if (process->type_instruc[1] == 0x50)
		process->reg[process->args[1]] = values[0];
	else
	{
		add = (process->args[1] % IDX_MOD) - IDX_MOD
			* ((((process->args[1]) / IDX_MOD) & 1));
		*(int *)(vm->core + ((process->pc + add) & (MEM_SIZE - 1))) = values[0];
		i = -1;
		while (++i < 4)
			vm->color[(process->pc + i + add)
				& (MEM_SIZE - 1)] = process->color + 4;
	}
	free(values);
}
