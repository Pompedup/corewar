/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_players.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 15:40:17 by ccoupez           #+#    #+#             */
/*   Updated: 2018/10/18 16:46:46 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
********************************************************************************
**	get_info_player fills in player->header
** je remplie la structure header(ds op.h avec magic, name, p_s et comment)
** et je recupere le programme du champion
********************************************************************************
*/

void	get_info_player(t_player *player, t_corevm *vm, int i)
{
	int	fd;

	if ((fd = open(vm->argv[i], O_RDONLY)) == -1)
		ft_error(vm, ft_strjoin(ERR_MESS_5, vm->argv[i]), 1);
	read_magic(player, vm, fd);
	read_name(player, vm, fd);
	read_prog_size(player, vm, fd);
	read_comment(player, vm, fd);
	read_programme(player, vm, fd);
	if (close(fd) == -1)
		ft_error(vm, ft_strjoin(ERR_MESS_6, vm->argv[i]), 1);
}

/*
********************************************************************************
**	init_variable initializes the attributes of t_player elements
********************************************************************************
*/

void	init_variable(t_corevm *vm, t_player *player, int num, int index_color)
{
	header_t			*header;

	if (!(header = ft_memalloc(sizeof(header_t))))
		ft_error(vm, FAIL_MEMALLOC_2, 0);
	player->header = header;
	player->num = num;
	player->color = index_color;
}

/*
********************************************************************************
**	create_player uses double pointer to add at the end of the list
**	vm->info->first_player the latest link containing the player info
** je cree un maillon t_player que je lie a la structure t_info_players
********************************************************************************
*/

void	create_player(t_corevm *vm, int num, int index)
{
	t_player			**player;
	static int			index_color = 0;

	player = &vm->info->first_player;
	while (*player)
		player = &(*player)->next;
	if (!(*player = ft_memalloc(sizeof(t_player))))
		ft_error(vm, FAIL_MEMALLOC_1, 0);
	(*player)->name_file = vm->argv[index];
	init_variable(vm, (*player), num, index_color);
	index_color++;
	get_info_player((*player), vm, index);
	vm->info->nb_players++;
}
