/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 12:02:04 by ccoupez           #+#    #+#             */
/*   Updated: 2018/07/17 16:31:09 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <fcntl.h>

void	get_dump(t_corevm *vm, int i)
{
	int		j;

	j = 0;
	while (ft_isdigit(vm->argv[i + 1][j]) && vm->argv[i + 1][j])
		j++;
	if (vm->argv[i + 1][j] != '\0')
		ft_error(vm, 0); // mettre le bon num derror (genre usage dump)
	vm->dump = ft_atoi(vm->argv[i + 1]);
}

int		unused_num(t_corevm *vm, int num)	
{
	int		i;

	i = 0;
	while (vm->players[i] && i < MAX_PLAYERS)
	{
		if (num == vm->players[i]->num)
			return (0);
		i++;
	}
	return (1);
}

void	get_file(t_corevm *vm, int i)
{
	int		fd;
	int		ret;
	char	buffer[TOTAL_SIZE + 1];
	int a = 0;

	printf(" get file vm->argv[i] -%s-\n", vm->argv[i]);
	if (ft_strlen(vm->argv[i]) > 4 && ft_strstr(vm->argv[i], ".cor\0"))
	{
		if ((fd = open(vm->argv[i], O_RDONLY)) == -1)
			ft_error(vm, 3);// num error probleme ouverture de fichier!!!
		printf("fd %d \n", fd);
		if ((ret = read(fd, buffer, TOTAL_SIZE + 1)) == -1)
			ft_error(vm, -3); // num error probleme de lecture!!!
		printf("ret %d \n", ret);
		buffer[ret] = '\0';
	//	while (buffer[a])
			a++;
	//	printf("aaaa %d\n", a);
	//	printf("buffer :\n%s\n",buffer);
	//	ft_putendl(buffer);
		//write(1, buffer, ret);
		vm->players[vm->nb_players]->file = ft_strdup(buffer);	print_player(vm->argv[i], i);	
		if (ret > TOTAL_SIZE)
			ft_error(vm, 4); //num error fichier trop grand!!!
	//	vm->players[vm->nb_players]->file[ret] = '\0';
		if (close(fd) == -1)
			ft_error(vm, 4);
	}
	else
		ft_error(vm, -4);
}

void    add_player_with_num(t_corevm *vm, int i)
{
	int j;
	int num;

	j = 0;
	printf("with num vm->nb_players %d\n", vm->nb_players);
	printf("le num du joueur -%s-\n", vm->argv[i + 1]);
	while (ft_isdigit(vm->argv[i + 1][j]) && vm->argv[i + 1][j])
		j++;
	if (vm->argv[i + 1][j] != '\0')
		ft_error(vm, 1); // mettre le bon num derror (genre -n veut un num apres)
	num = ft_atoi(vm->argv[i + 1]);
	if (num <= MAX_PLAYERS && unused_num(vm, num))
	{
		if (!(vm->players[vm->nb_players] = malloc(sizeof(t_players))))
			ft_error(vm, 2); //num malloc error
		vm->players[vm->nb_players]->num = num;
		vm->players[vm->nb_players]->color = 0; //?voir comment on met les couleurs (avec des defines?)
		vm->players[vm->nb_players]->file = NULL;
		get_file(vm, i + 2);
		vm->nb_players++;
	}
}

void    add_player(t_corevm *vm, int i)
{
	int num;

	num = 1;
	printf("no num vm->nb_players %d\n", vm->nb_players);
	if (ft_strlen(vm->argv[i]) > 4 && ft_strstr(vm->argv[i], ".cor\0"))
	{
		while (num <= MAX_PLAYERS && !(unused_num(vm, num)))
			num++;
		if (num > MAX_PLAYERS)
			ft_error(vm, 5); //num error il y a trop de joueur!!
		if (!(vm->players[vm->nb_players] = malloc(sizeof(t_players))))
			ft_error(vm, 6); //num malloc error
        vm->players[vm->nb_players]->num = num;
		vm->players[vm->nb_players]->color = 0; //?voir comment on met les couleurs (avec des defines?)
		vm->players[vm->nb_players]->file = NULL;
		get_file(vm, i);
		printf("4vm->argv[i] %s\n", vm->argv[i]);
        vm->nb_players++;
    }
    else
        ft_error(vm, 1); //le nom du fichier champion nest pas bon!!
}

void    parse_argv(t_corevm *vm)
{
    int i; 
    int nbr;

	i = 1;
    nbr = 0;
	if (ft_strequ(vm->argv[1], "-dump"))
	{
		get_dump(vm, 1);
		i = 3;
	}
    while (vm->argv[i])
	{
		printf("---------vm->argv[i] --%s--\n", vm->argv[i]);
        if (ft_strequ(vm->argv[i], "-visu"))
			vm->visu = 1;
		if (ft_strstr(vm->argv[i], ".cor\0")) 
		{
			printf("\n nn---- \n");
			add_player(vm, i);
		}
    	if (ft_strequ(vm->argv[i], "-n"))
		{
			printf("\n wn---- \n");
            add_player_with_num(vm, i);
			i += 2;
        }
        if (vm->nb_players > MAX_PLAYERS)
            ft_error(vm, 7); //num error il y a trop de joueur!!
		i++;
	}
}