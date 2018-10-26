/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_zjump.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecesari <ecesari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:33:22 by ccoupez           #+#    #+#             */
/*   Updated: 2018/10/26 13:03:17 by ecesari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
********************************************************************************
** 0x09
** jump -> fait un saut à l'adresse passée en parametre
** SI le carry est a 1
** si le carry est a 0 il ne fait rien mais consomme le meme nb de cycle
** Usage : zjmp S(D2)
********************************************************************************
*/

void	ft_zjmp(t_corevm *vm, t_process *process)
{
	ft_printf("dans zjmp process->carry %d \n", process->carry);
	get_two_octets(vm, process, 0);
	if (!process->carry)
		return ;
	if (vm->color[process->pc & (MEM_SIZE - 1)] < 12
		&& vm->color[process->pc & (MEM_SIZE - 1)] > 7)
		vm->color[process->pc & (MEM_SIZE - 1)] -= 8;
	else if (vm->color[process->pc & (MEM_SIZE - 1)] == 12)
		vm->color[process->pc & (MEM_SIZE - 1)]++;
	process->pc += ((process->args[0]) % IDX_MOD);
	process->pc = process->pc & (MEM_SIZE - 1);
	process->pc_tmp = 0;
}
