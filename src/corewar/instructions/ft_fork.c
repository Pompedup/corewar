/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:40:03 by ccoupez           #+#    #+#             */
/*   Updated: 2018/10/18 19:08:34 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
********************************************************************************
** 0x0c
** fork -> cree un nouveau programme qui est execute a ladresse :
** (PC + (first parameter % IDX_MOD)
** Fork %34 crée un nouveau programme a (PC + (34 % IDX_MOD)
** Le nouveau programme herite des differents etats du pere
** Usage : fork S(D2)
** ft_printf(" process->args[0]  %x\n", (process->args[0] ));
** ft_printf(" (process->args[0] & (IDX_MOD - 1) %d\n", (process->args[0]
** & (IDX_MOD - 1)));
** ft_printf("FORKKKKKKKKK fork->pc %d\n)",  fork->pc);
**
**
********************************************************************************
*/

void	ft_fork(t_corevm *vm, t_process *process)
{
	int			i;
	t_player	*tmp_player;
	t_process	*fork;

	tmp_player = vm->info->first_player;
	fork = NULL;
	get_two_octets(vm, process, 0);
	while (ft_strcmp(process->name, tmp_player->header->prog_name)
		&& tmp_player)
		tmp_player = tmp_player->next;
	if (tmp_player)
		fork = create_process(vm, ((process->pc + (process->args[0] % IDX_MOD))
			& (MEM_SIZE - 1)), tmp_player);
	i = 0;
	while (i < REG_NUMBER)
	{
		fork->reg[i] = process->reg[i];
		i++;
	}
	fork->carry = process->carry;
}
