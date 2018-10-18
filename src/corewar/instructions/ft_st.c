/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 11:07:13 by ccoupez           #+#    #+#             */
/*   Updated: 2018/10/18 16:27:35 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
********************************************************************************
** 0x03
** st -> store, met la valeur du 1er arg(un registre) dans le 2eme
** Usage : st S(RG), D(RG/ID)
** ft_printf("STORE value[0] x '%x' value[1] x '%d'\n", values[0], values[1]);
** ft_printf("STORE value[0] d '%d' value[1] d '%d'\n", values[0], values[1]);
** ft_printf("STORE process->args[1] '%d'  \n", (short)process->args[1]);
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
