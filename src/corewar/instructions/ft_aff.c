/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecesari <ecesari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:36:44 by ccoupez           #+#    #+#             */
/*   Updated: 2018/10/29 16:47:11 by ecesari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
********************************************************************************
**	ft_aff
** 	opcode 0x10, changes the carry if aff is null
** 	usage : aff ARG_1(RG)
**	displays the character of which the ASCII code (%256) is stored in ARG_1
********************************************************************************
*/

void		ft_aff(t_corevm *vm, t_process *process)
{
	unsigned char	c;

	get_one_octet(vm, process, 0);
	if (process->good_reg)
	{
		c = (char)(process->reg[process->args[0]] % 256);
		write(1, &c, 1);
	}
	process->carry = (process->reg[process->args[0]]) ? 0 : 1;
}
