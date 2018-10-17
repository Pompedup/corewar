/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecesari <ecesari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 19:32:17 by ecesari           #+#    #+#             */
/*   Updated: 2018/10/16 19:32:20 by ecesari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
********************************************************************************
** 0x10
** aff -> Elle prend en paramètre un registre
** et affiche le caractère dont le code ascii est présent dans ce registre
** (un modulo 256 est applique au code ascii,
** le caractère est affiché sur la sortie standard)
** Ex: ld %52,r3
** aff r3
** affiche '*' sur la sortie standard
********************************************************************************
*/

//Usage : aff S(RG)
void		ft_aff(t_corevm *vm, t_process *process)
{
	unsigned char	c;

	//ft_printf("\tAFFFFF'\n");
	process->pc_tmp++;
	get_one_octet(vm, process, 0);
	//ft_printf("\tprocess->args[0] hexa '%x'\n", process->args[0]);
	//ft_printf("\tAFFFFFprocess->reg[process->args[0]] hexa '%x'\n", process->reg[process->args[0]]);
	if (process->good_reg)
	{
		c = (char)(process->reg[process->args[0]] % 256);
		write(1, &c, 1);
		// write(1, "pourri\n", 7);
	}
	//ft_printf("AFF c '%c'\t", c);
//	ft_printf("\n");
}
