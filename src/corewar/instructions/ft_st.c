/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecesari <ecesari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 11:07:13 by ccoupez           #+#    #+#             */
/*   Updated: 2018/10/09 17:21:59 by ecesari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"


/*
** 0x03
** st -> store, met la valeur du 1er arg(un registre) dans le 2eme
** . Par exemple, st r1, 42 stocke la
valeur de r1 à l’adresse (PC + (42 % IDX_MOD))

** st r3,r8 copies r3 in r8
** ou st r3, r8 - copie r3 dans r8
*/

//Usage : st S(RG), D(RG/ID)
void	ft_st(t_corevm *vm, t_process *process)
{
	int	*values;
	int i;

	i = 0;
	get_args(vm, process, g_op_tab[process->type_instruc[0]]);
	values = get_values(vm, process, 1, 0);
	ft_printf(" __________________STORE values[0] hexa '%x' values[1] hexa '%x' \n", values[0], values[1]);
	if (values)
	{
		if (process->type_instruc[1] == 0x50)
		{
			process->reg[process->args[1]] = values[0];
			ft_printf(" _____________________STORE RG process->reg[process->args[1]] hexa %x \n", process->reg[process->args[1]]);
		}
		else
		{
			*(unsigned int *)(vm->core + ((process->pc + (process->args[1] & (IDX_MOD - 1))) & (MEM_SIZE - 1))) = values[0];
			while (i < 4)
			{
				vm->color[(process->pc + i + (process->args[1] & (IDX_MOD - 1))) & (MEM_SIZE - 1)] = process->color + 4;
				i++;
			}
			ft_printf(" STORE IND vm->core[(process->pc + (values[1] & (IDX_MOD - 1))) & (MEM_SIZE - 1)] hexa %x \n", vm->core[(process->pc + (values[1] & (IDX_MOD - 1))) & (MEM_SIZE - 1)]);
		}
		free(values);
	}
}
