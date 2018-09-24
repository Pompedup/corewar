/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file_players.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecesari <ecesari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 14:08:14 by ccoupez           #+#    #+#             */
/*   Updated: 2018/09/24 18:03:38 by ecesari          ###   ########.fr       */
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
		ft_read_error(vm, ft_strjoin(ERR_MESS_8, player->name_file), fd); // num error probleme de lecture!!!
	ft_memrev(magic, 4);
	player->header->magic = *(unsigned int *)magic;
	//printf("player->header->magic %x \n", player->header->magic);
	//print_memory(magic, 4);
	if (player->header->magic != COREWAR_EXEC_MAGIC)
		ft_error(vm, ERR_MESS_7, 0); //le numero magique nest pas bon :(!!
}

/*
********************************************************************************
**  read_name
********************************************************************************
*/

void	read_name(t_player *player, t_corevm *vm, int fd)
{
	int ret;

	if ((ret = read(fd, player->header->prog_name, PROG_NAME_LENGTH + 4)) == -1) //+4 pour le '\0'
		ft_read_error(vm, ft_strjoin(ERR_MESS_9, player->name_file), fd); // num error probleme de lecture!!!
	player->header->prog_name[ret] = '\0';
	//write(1, "name : ", 7);
	//write(1, player->header->prog_name, ret);
	//write(1, "\n", 1);
	//print_memory(player->header->prog_name, ret);
}

/*
********************************************************************************
**  read_prog_size
********************************************************************************
*/

void	read_prog_size(t_player *player, t_corevm *vm, int fd)
{
	int		ret;
	char	psize[4];

	if ((ret = read(fd, psize, 4)) == -1)
		ft_read_error(vm, ft_strjoin(ERR_MESS_10, player->name_file), fd); // num error probleme de lecture!!!
	//printf("player->header->prog_size %x \n", player->header->prog_size);
	//print_memory(psize, 4);
	ft_memrev(psize, 4);
	player->header->prog_size = *(unsigned int *)psize;
	if (player->header->prog_size > CHAMP_MAX_SIZE)
		ft_error(vm, ERR_MESS_11, 0); //votre champion est trop gros!! (∩｀-´)
	//printf("player->header->prog_size %x \n", player->header->prog_size);
	//print_memory(psize, 4);
}

/*
********************************************************************************
**  read_comment
********************************************************************************
*/

void	read_comment(t_player *player, t_corevm *vm, int fd)
{
	int ret;

	if ((ret = read(fd, player->header->comment, COMMENT_LENGTH + 4)) == -1)// +4 pour le '\0'
		ft_read_error(vm, ft_strjoin(ERR_MESS_12, player->name_file), fd); // num error probleme de lecture!!!
	player->header->comment[ret] = '\0';
	//write(1, "comment : ", 10);
	//write(1, player->header->comment, ret);
	//write(1, "\n", 1);
	//print_memory(player->header->comment, ret);
}

/*
********************************************************************************
**  read_programme
********************************************************************************
*/

void	read_programme(t_player *player, t_corevm *vm, int fd)
{
	int ret;

	if ((ret = read(fd, player->process, CHAMP_MAX_SIZE + 1)) == -1)
		ft_read_error(vm, ft_strjoin(ERR_MESS_13, player->name_file), fd); // num error probleme de lecture!!!
	if (ret > CHAMP_MAX_SIZE)
		ft_error(vm, ERR_MESS_11, 0); //votre champion est trop gros!!
	player->process[ret] = '\0';
	if ((unsigned int)ret != player->header->prog_size)
		ft_error(vm, ERR_MESS_14, 0); //difference entre la taille reel de votre proramme et l'int prog_size :0 !!
	player->len_process = ret; //potentiellement a retirer car doublon avec header->prog_size
	//write(1, "process : \n", 11);
	//print_memory(player->process, ret);
	//	write(1, "\n", 1);
}
