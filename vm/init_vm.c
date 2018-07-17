/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 15:22:28 by ccoupez           #+#    #+#             */
/*   Updated: 2018/07/17 15:27:37 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** on init la vm avec le nombre de champion le nombre de cycle
** et avec lallocation de la memoire de la vm a MEM_SIZE
*/

void		init_vm(char **av, t_corevm *vm)
{
    int	i;

    i = 0;
	vm->argv = av;
	vm->nb_cycles = 0;
	vm->nb_players = 0;
	vm->dump = 0;
	vm->visu = 0;
	while (i < MAX_PLAYERS)
		vm->players[i++] = NULL;
    ft_bzero(vm->core, MEM_SIZE);
}