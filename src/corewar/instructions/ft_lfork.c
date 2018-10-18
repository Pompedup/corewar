/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lfork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:40:58 by ccoupez           #+#    #+#             */
/*   Updated: 2018/10/18 16:41:06 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
********************************************************************************
** 0x0f
** lfork -> long fork, meme chose que fork sans le % IDX_MOD
** Usage : lfork S(D2)
********************************************************************************
*/

void		ft_lfork(t_corevm *vm, t_process *process)
{
	int			i;
	t_player	*tmp;
	t_process	*fork;

	tmp = vm->info->first_player;
	fork = NULL;
	get_two_octets(vm, process, 0);
	while (ft_strcmp(process->name, tmp->header->prog_name) && tmp)
		tmp = tmp->next;
	if (tmp)
		fork = create_process(vm, ((process->pc + process->args[0])
			& (MEM_SIZE - 1)), tmp);
	i = 0;
	while (i < REG_NUMBER)
	{
		fork->reg[i] = process->reg[i];
		i++;
	}
}
