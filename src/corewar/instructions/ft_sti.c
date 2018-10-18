/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecesari <ecesari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:29:56 by ccoupez           #+#    #+#             */
/*   Updated: 2018/10/18 17:07:36 by ecesari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
********************************************************************************
** 0x0b
** sti -> va copier le 1er param dans une adresse obtenu grace au 2 autres
** sti r2,%4,%5 -
** sti copies REG_SIZE octets de r2 a laddresse (4 + 5)
** ici les params 2 et 3 sont des index
** si ce sont des registres, on utilisera leur contenu comme un index
** Usage : sti S(RG), S(RG/ID/D2), S(RG/D2)
********************************************************************************
*/

void		ft_sti(t_corevm *vm, t_process *process)
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
