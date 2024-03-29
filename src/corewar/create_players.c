/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_players.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecesari <ecesari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 15:40:17 by ccoupez           #+#    #+#             */
/*   Updated: 2018/11/01 14:31:06 by ecesari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
********************************************************************************
**	lenght_display_string
********************************************************************************
*/

int		lenght_display_string(char *string, int padding)
{
	int		lenght;
	char	*new_line;

	if ((new_line = ft_strchr(string, '\n')))
	{
		if (new_line - string > padding)
			lenght = padding;
		else
			lenght = new_line - string;
	}
	else
		lenght = (int)ft_strlen(string) > padding ? padding : ft_strlen(string);
	return (lenght);
}

/*
********************************************************************************
**	get_info_player fills in player->header with
**	- the magic number
**	- the name of the program
**	- the size of the program
**	- the comment
**	- the actual program
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
	t_header			*header;

	if (!(header = ft_memalloc(sizeof(t_header))))
		ft_error(vm, FAIL_MEMALLOC_2, 0);
	player->header = header;
	player->num = num;
	player->color = index_color;
}

/*
********************************************************************************
**	create_player uses double pointer to add at the end of the list
**	vm->info->first_player the latest link containing the player info
**	and then it initializes the variable and gets all the relevant info
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
	get_info_player((*player), vm, index);
	index_color++;
	vm->info->nb_players++;
}
