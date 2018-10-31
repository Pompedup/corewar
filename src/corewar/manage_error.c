/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecesari <ecesari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 18:32:47 by ccoupez           #+#    #+#             */
/*   Updated: 2018/10/19 19:53:14 by ecesari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
********************************************************************************
**	ft_error prints on stder the error message and calls free_vm
**	can't perform open - read - close
********************************************************************************
*/

void	ft_error(t_corevm *vm, char *mess_error, int to_free)
{
	if (ft_strstr(mess_error, ERR_MESS_11))
		ft_fprintf(2, "Error: File %s (%d bytes > %d bytes).\n", mess_error,
			vm->info->first_player->header->prog_size, CHAMP_MAX_SIZE);
	else
		ft_fprintf(2, "Error: %s.\n", mess_error);
	if (to_free)
		ft_strdel(&mess_error);
	if (vm)
		free_vm(vm);
	exit(0);
}

/*
********************************************************************************
** ft_read_error
********************************************************************************
*/

void	ft_read_error(t_corevm *vm, char *mess_error, int fd)
{
	if (close(fd) == -1)
		ft_error(vm,
			ft_strjoin(ERR_MESS_6, vm->info->first_player->name_file), 1);
	ft_error(vm, mess_error, 1);
}
