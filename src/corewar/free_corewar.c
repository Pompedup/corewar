/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_corewar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 14:29:06 by ecesari           #+#    #+#             */
/*   Updated: 2018/10/19 15:54:42 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
********************************************************************************
**	free_vm_info_process frees every processes created by each player
********************************************************************************
*/

void	free_vm_info_process(t_corevm *vm, t_process* process_to_delete)
{
	t_process	*tmp;

	if (process_to_delete)
	{
		tmp = process_to_delete->next;
		free(process_to_delete);
		free_vm_info_process(vm, tmp);
	}
}

/*
********************************************************************************
**	free_vm_info_player aims at freeing each vm->info->player created
**	it also frees the header of each player
**	and calls free_vm_info_process
********************************************************************************
*/

void	free_vm_info_player(t_corevm *vm, t_player* player_to_delete)
{
	t_player	*tmp;

	if (player_to_delete)
	{
		tmp = player_to_delete->next;
		free(player_to_delete->header);// free_vm_info_player_header(vm, player_to_delete->header);
		free_vm_info_process(vm, player_to_delete->process);
		free(player_to_delete);
		free_vm_info_player(vm, tmp);
	}
}

/*
********************************************************************************
**	free_vm aims at freeing every structure malloced during corewar
**	- vm->info
**	- vm->info->player
**	- vm->info->player->header
**	- vm->info->process
**	- (values used in instruction are freed at the end of the instruction)
**
********************************************************************************
*/

void	free_vm(t_corevm *vm)
{
	if (vm->info)
	{
		free_vm_info_player(vm, vm->info->first_player);
		free(vm->info);
	}
}