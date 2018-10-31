/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:35:48 by ccoupez           #+#    #+#             */
/*   Updated: 2018/10/18 16:36:31 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
********************************************************************************
** 0x04
** additionne l'arg1 et l'arg2 et met le resultat dans l'arg3
** modifie le carry
** Usage : add S(RG), S(RG), D(RG)
** ft_printf(" ADD values[0] %d  values[1] %d process->reg[process->args[2]]
** %d\n", values[0], values[1], process->reg[process->args[2]]);
********************************************************************************
*/

void		ft_add(t_corevm *vm, t_process *process)
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
