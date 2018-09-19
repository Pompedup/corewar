/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 11:07:13 by ccoupez           #+#    #+#             */
/*   Updated: 2018/09/19 16:57:47 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

extern t_op	g_op_tab[];

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
	if (!(test_args(process, g_op_tab[process->type_instruc[0]])))
		return ;
	get_args(vm, process, g_op_tab[process->type_instruc[0]]);
	if (process->type_instruc[1] == 0x50) //{T_REG, T_REG} || (process->type_instruc[1] >> 4) & 3 == 1
		process->reg[process->args[1]] = process->reg[process->args[0]]; //ce qu'il y a ds le reg de l'arg 1 je le met dans le reg designé larg 2
	if (process->type_instruc[1] == 0x70) //{T_REG, T_IND} || (process->type_instruc[1] >> 4) & 3 == 2
		vm->core[(process->pc + (process->args[1] % IDX_MOD)) % MEM_SIZE] //je calcul ladress indirectement en ajoutant le nbr l'arg 2 a mon pc
			= process->reg[process->args[0]]; //et j'y' met la valeur quil y a dans le registre de larg 1

}
