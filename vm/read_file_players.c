/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file_players.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 14:08:14 by ccoupez           #+#    #+#             */
/*   Updated: 2018/07/20 16:43:25 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"


/*
**  (∩｀-´)⊃━☆ﾟ.*･｡ﾟ
*/

void	read_magic(t_player *player, t_corevm *vm, int fd)
{
	int		ret;
	char	buf[4];

	if ((ret = read(fd, buf, 4)) == -1)
		ft_error(vm, -3); // num error probleme de lecture!!!
	ft_strrev(buf, 4);
	player->header->magic = *(unsigned int *)buf;

	//printf("player->header->magic %x \n", player->header->magic);
	//print_memory(buf, 4);

	if (player->header->magic != COREWAR_EXEC_MAGIC)
		ft_error(vm, 34); //le numero magique nest pas bon :(!!
}

void	read_name(t_player *player, t_corevm *vm, int fd)
{
	int ret;

	if ((ret = read(fd, player->header->prog_name, PROG_NAME_LENGTH)) == -1)
		ft_error(vm, -3); // num error probleme de lecture!!!
	player->header->prog_name[ret] = '\0';

	//write(1, "name : ", 7);
	//write(1, player->header->prog_name, ret);
	//write(1, "\n", 1);
	//print_memory(player->header->prog_name, ret);
}

void	read_prog_size(t_player *player, t_corevm *vm, int fd)
{
	int		ret;
	char	buf[8];

	if ((ret = read(fd, buf, 8)) == -1)
		ft_error(vm, -3); // num error probleme de lecture!!!
	ft_strrev(buf, 8);
	player->header->prog_size = *(unsigned int *)buf;
	if (player->header->prog_size > CHAMP_MAX_SIZE)
		ft_error(vm, 333); //votre champion est trop gros!!

	//printf("player->header->prog_size %x \n", player->header->prog_size);
	//print_memory(buf, 8);
}

void	read_comment(t_player *player, t_corevm *vm, int fd)
{
	int ret;

	if ((ret = read(fd, player->header->comment, COMMENT_LENGTH + 4)) == -1)//ALORS POURQUOI +4 ????? je sais pas mais sinon la taille prog size et celle du programme reel ne match pas :'(
		ft_error(vm, -3); // num error probleme de lecture!!!
	player->header->comment[ret] = '\0';

	//write(1, "comment : ", 10);
	//write(1, player->header->comment, ret);
	//write(1, "\n", 1);
	//print_memory(player->header->comment, ret);
}

void	read_programme(t_player *player, t_corevm *vm, int fd)
{
	int ret;

	if ((ret = read(fd, player->process, CHAMP_MAX_SIZE + 1)) == -1)
		ft_error(vm, -3); // num error probleme de lecture!!!
	if (ret > CHAMP_MAX_SIZE)
		ft_error(vm, 3); //votre champion est trop gros!!
	player->process[ret] = '\0';
	printf("ret %d\n", ret);
	if (ret != player->header->prog_size) 
		ft_error(vm, 19); //difference entre la taille reel de votre proramme et l'int prog_size :0 !!
	player->len_process = ret;

	//write(1, "process : \n", 11);
	//print_memory(player->process, ret);
	//	write(1, "\n", 1);
}
