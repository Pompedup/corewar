/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   register_players.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 15:40:17 by ccoupez           #+#    #+#             */
/*   Updated: 2018/09/04 11:25:34 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** je remplie la structure header(ds op.h avec magic, name, p_s et comment)
** et je recupere le programme du champion
*/

void	get_info_player(t_player *player, t_corevm *vm, int i)
{
	int	fd;

	//printf(" get file vm->argv[i] -%s-\n", vm->argv[i]);
	if (ft_strlen(vm->argv[i]) > 4 && ft_strstr(vm->argv[i], ".cor\0"))
	{
		if ((fd = open(vm->argv[i], O_RDONLY)) == -1)
			ft_error(vm, 3);// open error :O
		read_magic(player, vm, fd);
		read_name(player, vm, fd);
		read_prog_size(player, vm, fd);
		read_comment(player, vm, fd);
		read_programme(player, vm, fd);
		if (close(fd) == -1)
			ft_error(vm, 13); //close error :'(
	}
	else
		ft_error(vm, -4);
}

void	init_variable(t_corevm *vm, t_player *player, int num)
{
//	int i;
	header_t	*header;

	if (!(header = malloc(sizeof(header_t))))
		ft_error(vm, -6); //malloc error
	player->header = header;
	player->num = num;
	player->color = 0; //?voir comment on met les couleurs (avec des defines?)

}

/*
** je cree un maillon t_player que je lie a la structure t_info_players
*/

void	create_player(t_corevm *vm, int num, int index)
{
	t_player	*player;
	t_player	*tmp;

	if (!(player = malloc(sizeof(t_player))))
		ft_error(vm, -6); //malloc error
	player->name_file = vm->argv[index]; // a supprimer quand on a fini le projet cetait juste pour afficher
	init_variable(vm, player, num);
	get_info_player(player, vm, index);
	if (vm->info->first_player == NULL)
		vm->info->first_player = player;
	else
	{
		tmp = vm->info->first_player;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = player;
	}
	vm->info->nb_players++;
}
