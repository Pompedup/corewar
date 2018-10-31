/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:41:15 by ccoupez           #+#    #+#             */
/*   Updated: 2018/10/18 16:43:51 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
********************************************************************************
** 0x0a
** ldi -> load a l'indice
** modifie le carry
** les parametres 1 et 2 sont des index.
** quon copie dans r1
** Usage : ldi S(RG/ID/D2), S(ID/D2), D(RG)
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
