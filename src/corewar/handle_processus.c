/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_processus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 15:13:34 by ccoupez           #+#    #+#             */
/*   Updated: 2018/09/13 11:51:11 by ccoupez          ###   ########.fr       */
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

    if (!(process = malloc(sizeof(t_process))))
        ft_error(vm, -66); //malloc error
	i = 1;
	while (i < REG_NUMBER)
		process->reg[i++] = 0;
    i = 0;
    while (i < 5)
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
