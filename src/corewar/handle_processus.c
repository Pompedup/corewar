/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_processus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecesari <ecesari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 15:13:34 by ccoupez           #+#    #+#             */
/*   Updated: 2018/10/25 19:01:08 by ecesari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
********************************************************************************
**  put_process_front enables the latest player to play first
** le dernier joueur né joue en premier.
********************************************************************************
*/

void		put_process_front(t_process **first, t_process *process)
{
	process->next = *first;
	*first = process;
}

/*
********************************************************************************
**  create_process translates the player information into a process
********************************************************************************
*/

t_process	*create_process(t_corevm *vm, int pc, t_player *player)
{
	t_process	*process;
	int			i;

	if (!(process = ft_memalloc(sizeof(t_process))))
		ft_error(vm, FAIL_MEMALLOC_3, 0);
	process->pc = pc;
	process->color = player->color;
	process->color_live = -1;
	if (vm->color[pc] < 8)
		vm->color[pc] =
			vm->color[pc] < 4 ? vm->color[pc] + 8 : vm->color[pc] + 4;
	if (vm->color[pc] == 13)
		vm->color[pc]--;
	process->num_player = player->num;
	process->reg[0] = player->num;
	ft_memrev(&process->reg[0], 4);
	process->good_reg = 1;
	i = -1;
	while (++i < 2)
		process->type_instruc[i] = -1;
	ft_strcpy(process->name, player->header->prog_name);
	put_process_front(&(vm->info->first_processus), process);
	return (process);
}
