/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:39:08 by ccoupez           #+#    #+#             */
/*   Updated: 2018/10/18 16:39:49 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
********************************************************************************
** 0x02
** ld -> load charge la valeur du 1er parametre dans le registre (2eme param)
** modifie le carry
** Transfert direct RAM > Registre.
** Si la valeur du 1er param = 0 , alors le carry passe a 1, sinon 0.
** Usage : ld S(ID/D4), D(RG)
** ft_printf("LD process->type_instruc[1] x%x\n", process->type_instruc[1]);
** ft_printf(" LOAD reg args[1] %d values[0] int %d\n",
** process->args[1], values[0]);
********************************************************************************
*/

void	ft_ld(t_corevm *vm, t_process *process)
{
	int	*values;

	get_args(vm, process, g_op_tab[process->type_instruc[0]]);
	if (process->good_reg)
	{
		values = get_values(vm, process, 1, 0);
		if (values)
		{
			process->reg[process->args[1]] = (int)values[0];
			process->carry = values[0] == 0 ? 1 : 0;
			free(values);
		}
	}
}
