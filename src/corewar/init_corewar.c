/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_corewar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 15:22:28 by ccoupez           #+#    #+#             */
/*   Updated: 2018/10/11 16:43:07 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
********************************************************************************
**	init_vm initializes every attributes of t_corevm *vm
**	and mallocs vm->info
**
** la seule chose qui est malloc pour le moment
** cest les mailons de la liste chainee des joueurs
** et la structure info_player (1 int et lie a la liste chaine des joueurs)
********************************************************************************
*/

void		init_vm(char **av, t_corevm *vm)
{
	int	i;

	i = 0;
	ft_bzero(vm, sizeof(t_corevm));
	while (i < MEM_SIZE)
		vm->color[i++] = 13;
	vm->argv = av;
	vm->dump = -1;
	vm->octet_line_viz = ft_sqrt(MEM_SIZE);
	vm->cycle_to_die = CYCLE_TO_DIE;
	if (!(vm->info = ft_memalloc(sizeof(t_info))))
		ft_error(vm, FAIL_MEMALLOC_0, 0);
}
