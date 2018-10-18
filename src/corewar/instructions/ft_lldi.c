/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lldi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:45:30 by ccoupez           #+#    #+#             */
/*   Updated: 2018/10/18 16:46:03 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
********************************************************************************
** 0x0e
** lldi -> long long load indice, comme le load indice sans le % IDX_MOD
** les parametres 1 et 2 sont des index.
** qu'on dditionnne on nomme cette somme S.
** quon copie dans le 3eme arg qui est un registre
** modifie le carry
** Usage : lldi S(RG/ID/D2), S(ID/D2), D(RG)
** ft_printf("LONG LOAD INDICE values[0] x %x x %x \n", values[0], values[1]);
** ft_printf("LONG LOAD INDICE values[0] d %d d %d \n", values[0], values[1]);
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
