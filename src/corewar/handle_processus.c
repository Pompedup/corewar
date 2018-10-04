/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_processus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecesari <ecesari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 15:13:34 by ccoupez           #+#    #+#             */
/*   Updated: 2018/10/04 18:14:04 by ecesari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "corewar.h"


/*
********************************************************************************
**  put_process_front enables the latest player to play first
** le dernier joueur né joue en premier.
********************************************************************************
*/

void        put_process_front(t_process **first, t_process *process)
{
    process->next = *first;
    *first = process;
}

/*
********************************************************************************
**  create_process translates the player information into a process
** avant de placer les joueurs dans la core
** on les transformes en processus (on les mets dans une nouvelle sutructure "process")
** plus adaptée pour executer le jeu
********************************************************************************
*/

//color, num, header->prog_name
t_process	*create_process(t_corevm *vm, int pc, t_player *player)
{
    t_process   *process;
    int			i;

	i = 0;
    if (!(process = ft_memalloc(sizeof(t_process))))
        ft_error(vm, FAIL_MEMALLOC_3, 0);
    process->color = player->color;
    process->pc = pc;
    if (vm->color[pc] < 8)
        vm->color[pc] = vm->color[pc] < 4 ? vm->color[pc] + 8 : vm->color[pc] + 4;//pour les cas de fork
    process->reg[0] = player->num;
    while (i < 2)
	{
		process->type_instruc[i] = -1;
		i++;
	}
    ft_strcpy(process->name, player->header->prog_name);
    // printf("player->num %d\n", player->num);
    return (process);
}
