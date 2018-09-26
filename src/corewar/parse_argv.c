/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecesari <ecesari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 12:02:04 by ccoupez           #+#    #+#             */
/*   Updated: 2018/09/26 16:24:21 by ecesari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
********************************************************************************
**	add_player_with_num checks that the argv following -n is a positive int
**	then creates the player with that number
********************************************************************************
*/

void	add_player_with_num(t_corevm *vm, int i)
{
	int num;

	if ((!(ft_strisall(vm->argv[i + 1], &ft_isdigit)))\
		|| (ft_strlen(vm->argv[i]) > 10 || (ft_strlen(vm->argv[i]) == 10\
		&& ft_strcmp(vm->argv[i], "2147483647") > 0)))
		ft_error(vm, ERR_MESS_17, 0);
	num = ft_atoi(vm->argv[i + 1]);
	if (num == 0 || !unused_num(vm, num))
		ft_error(vm, ERR_MESS_18, 0);
	if (ft_strlen(vm->argv[i + 2]) < 4\
		|| ft_strcmp(ft_strstr(vm->argv[i + 2], ".cor"), ".cor"))
		ft_error(vm, ERR_MESS_4, 0);
	create_player(vm, num, i + 2);
}

/*
********************************************************************************
**	add_player checks that the file name is not empty
**	ajoute un joueur (sans numero pour le moment)
********************************************************************************
*/

void	add_player(t_corevm *vm, int i)
{
	if (ft_strlen(vm->argv[i]) < 4)
		ft_error(vm, ERR_MESS_4, 0);
	create_player(vm, 0, i);
}

/*
********************************************************************************
**	get_dump checks that the number of cycles given is a positive int
**	recupère	dump :
** Au bout de nbr_cycles cycles d’exécution, dump la mémoire sur la sortie
** standard,puis quitte la partie. (mémoire dumpée au format hexadécimal)
** avec 32 octets par ligne.
********************************************************************************
*/

void	get_dump(t_corevm *vm, int i)
{
	if ((!(ft_strisall(vm->argv[i], &ft_isdigit)))\
		|| (ft_strlen(vm->argv[i]) > 10 || (ft_strlen(vm->argv[i]) == 10\
		&& ft_strcmp(vm->argv[i], "2147483647") > 0)))
		ft_error(vm, ERR_MESS_2, 0);
	if (!(vm->dump = ft_atoi(vm->argv[i])))
		ft_error(vm, ERR_MESS_3, 0);
}

/*
********************************************************************************
** parse_argv
** parsing des champions (et 2 options : -dump (lié a nbr_cycle) et -visu)
********************************************************************************
*/

void	parse_argv(t_corevm *vm)
{
	int	i;

	i = 0;
	while (vm->argv[++i])
	{
		if (ft_strequ(vm->argv[i], "-dump") && vm->dump == 0)
			get_dump(vm, ++i);
		else if (ft_strequ(vm->argv[i], "-visu"))
			vm->visu = 1;
		else if (ft_strcmp(ft_strstr(vm->argv[i], ".cor"), ".cor") == 0)
			add_player(vm, i);
		else if (ft_strequ(vm->argv[i], "-n"))
		{
			add_player_with_num(vm, i);
			i += 2;
		}
		else
			ft_error(vm, ERR_MESS_1, 0);
		if (vm->info->nb_players > MAX_PLAYERS)
			ft_error(vm, ERR_MESS_15, 0);
	}
	if (vm->info->nb_players < 1)
		ft_error(vm, ERR_MESS_16, 0);
}
