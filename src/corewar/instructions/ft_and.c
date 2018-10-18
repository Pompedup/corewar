/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_and.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:37:03 by ccoupez           #+#    #+#             */
/*   Updated: 2018/10/18 16:38:44 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
********************************************************************************
** 0x06
** Applique un & (ET bit-à-bit) sur les deux premiers paramètres, et stocke le
** résultat dans le registre qui est le 3ème paramètre.
** Modifie le carry.
** Si la valeur resultante est egale a zero, le carry passe a un, sinon zero
**  Usage : and S(RG/ID/D4), S(RG/ID/D4), D(RG)
** ft_printf(" AND values[0] x %x  values[1] hexa %x\n", values[0], values[1]);
** ft_printf("process->reg[process->args[2]] hexa %x\n",
** process->reg[process->args[2]]);
********************************************************************************
*/

void		ft_and(t_corevm *vm, t_process *process)
{
	int	*values;

	get_args(vm, process, g_op_tab[process->type_instruc[0]]);
	if (process->good_reg)
	{
		values = get_values(vm, process, 3, 0);
		if (values)
		{
			process->reg[process->args[2]] = values[0] & values[1];
			process->carry = (process->reg[process->args[2]]) ? 0 : 1;
			free(values);
		}
	}
}
