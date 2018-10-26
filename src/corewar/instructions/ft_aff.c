/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecesari <ecesari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:36:44 by ccoupez           #+#    #+#             */
/*   Updated: 2018/10/26 13:14:02 by ecesari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
********************************************************************************
** 0x10
** affiche le caractère dont le code ascii est présent dans ce registre
** (un modulo 256 est applique au code ascii,
** Usage : aff S(RG)
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
