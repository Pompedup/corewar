/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_processus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecesari <ecesari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 15:13:34 by ccoupez           #+#    #+#             */
/*   Updated: 2018/09/24 17:58:59 by ecesari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "corewar.h"

/*
** le dernier joueur né joue en premier.
*/

void        put_process_front(t_process **first, t_process *process)
{
    process->next = *first;
    *first = process;
}

/*
** avant de placer les joueurs dans la core
** on les transformes en processus (on les mets dans une nouvelle sutructure "process")
** plus adaptée pour executer le jeu
*/

t_process	*create_process(t_corevm *vm, int pc, t_player *player)
{
    int         i;
    t_process   *process;

    if (!(process = ft_memalloc(sizeof(t_process))))
        ft_error(vm, "malloc error", 0); //malloc error
	i = 0;
    while (i < 2)
        process->type_instruc[i++] = -1;
    process->color = player->color;
    process->pc = pc;
	process->carry = 0;
	process->reg[0] = player->num;
    process->alive = 0;
    ft_strcpy(player->header->prog_name, process->name);
    printf("player->num %d\n", player->num);
    return (process);
}
