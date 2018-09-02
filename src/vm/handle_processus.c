/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_processus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 15:13:34 by ccoupez           #+#    #+#             */
/*   Updated: 2018/09/02 16:18:59 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "vm.h"

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

t_process	*create_process(t_corevm *vm, int pc, int num, unsigned int color)
{
    int         i;
    t_process   *process;

    if (!(process = malloc(sizeof(t_process))))
        ft_error(vm, -66); //malloc error
    process->color = color;
    process->pc = pc;
	process->carry = 0;
	process->reg[0] = num;
	i = 1;
	while (i < REG_NUMBER)
		process->reg[i++] = 0;
    printf("num %d\n", num);
    return (process);
}
