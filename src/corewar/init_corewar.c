/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_corewar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecesari <ecesari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 15:22:28 by ccoupez           #+#    #+#             */
/*   Updated: 2018/09/24 17:59:26 by ecesari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
********************************************************************************
**	init_vm
** la seule chose qui est malloc pour le moment
** cest les mailons de la liste chainee des joueurs
** et la structure info_player (1 int et lie a la liste chaine des joueurs)
********************************************************************************
*/

void		init_vm(char **av, t_corevm *vm)
{
	t_info	*info;

	ft_bzero(vm, sizeof(t_corevm));
	vm->argv = av;
	vm->cycle_to_die = CYCLE_TO_DIE;
	vm->nb_max_live = NBR_LIVE;
	if (!(info = ft_memalloc(sizeof(t_info))))
		ft_error(vm, FAIL_MEMALLOC_0, 0);
	vm->info = info;
}
