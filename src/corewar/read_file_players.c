/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file_players.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 14:08:14 by ccoupez           #+#    #+#             */
/*   Updated: 2018/10/18 15:56:59 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
********************************************************************************
**  read_magic reads for 4 bytes then reverses it into little endian
**	saves the result in an int (player->header->magic)
**	(∩｀-´)⊃━☆ﾟ.*･｡ﾟ
********************************************************************************
*/

void	read_magic(t_player *player, t_corevm *vm, int fd)
{
	int		ret;
	char	magic[4];

	if ((ret = read(fd, magic, 4)) == -1)
		ft_read_error(vm, ft_strjoin(ERR_MESS_8, player->name_file), fd);
	ft_memrev(magic, 4);
	player->header->magic = *(unsigned int *)magic;
	if (player->header->magic != COREWAR_EXEC_MAGIC)
		ft_error(vm, ERR_MESS_7, 0);
}

/*
********************************************************************************
**  read_name saves the program name into player->header->prog_name
********************************************************************************
*/

void	read_name(t_player *player, t_corevm *vm, int fd)
{
	int ret;

	if ((ret = read(fd, player->header->prog_name, PROG_NAME_LENGTH + 4)) == -1)
		ft_read_error(vm, ft_strjoin(ERR_MESS_9, player->name_file), fd);
	player->header->prog_name[ret] = '\0';
}

/*
********************************************************************************
**  read_prog_size saves the size of the program into player->header->prog_size
********************************************************************************
*/

void	read_prog_size(t_player *player, t_corevm *vm, int fd)
{
	int		ret;
	char	psize[4];

	if ((ret = read(fd, psize, 4)) == -1)
		ft_read_error(vm, ft_strjoin(ERR_MESS_10, player->name_file), fd);
	ft_memrev(psize, 4);
	player->header->prog_size = *(unsigned int *)psize;
	if (player->header->prog_size > CHAMP_MAX_SIZE)
		ft_error(vm, ft_strjoin(player->name_file, ERR_MESS_11), 1);
}

/*
********************************************************************************
**  read_comment saves the comment into player->header->comment
********************************************************************************
*/

void	read_comment(t_player *player, t_corevm *vm, int fd)
{
	int ret;

	if ((ret = read(fd, player->header->comment, COMMENT_LENGTH + 4)) == -1)
		ft_read_error(vm, ft_strjoin(ERR_MESS_12, player->name_file), fd);
	player->header->comment[ret] = '\0';
}

/*
********************************************************************************
**  read_programme saves the program into player->process
**	and the lenght of the program into player->len_process
********************************************************************************
*/

void	read_programme(t_player *player, t_corevm *vm, int fd)
{
	int ret;

	if ((ret = read(fd, player->process, CHAMP_MAX_SIZE + 1)) == -1)
		ft_read_error(vm, ft_strjoin(ERR_MESS_13, player->name_file), fd);
	if (ret > CHAMP_MAX_SIZE)
		ft_error(vm, ft_strjoin(player->name_file, ERR_MESS_11), 1);
	player->process[ret] = '\0';
	if ((unsigned int)ret != player->header->prog_size)
		ft_error(vm, ERR_MESS_14, 0);
	player->len_process = ret;
}
