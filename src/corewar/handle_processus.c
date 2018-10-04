/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_processus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecesari <ecesari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 15:13:34 by ccoupez           #+#    #+#             */
/*   Updated: 2018/10/04 15:14:49 by ecesari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "corewar.h"

/*
********************************************************************************
**
********************************************************************************
*/

t_color     *create_color(t_corevm *vm, t_player *player, int start)
{
    t_color **new_color;

    new_color = &vm->info->first_color;
    while (*new_color)
        new_color = &(*new_color)->next;
    if (!(*new_color = ft_memalloc(sizeof(t_color))))
        ft_error(vm, FAIL_MEMALLOC_4, 0);
    (*new_color)->color = player->color;
    (*new_color)->start = start;
}


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
