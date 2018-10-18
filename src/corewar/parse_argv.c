/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 12:02:04 by ccoupez           #+#    #+#             */
/*   Updated: 2018/10/18 12:21:33 by ccoupez          ###   ########.fr       */
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
**	then creates the player without a specific number
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
**
** -------------------------- commentaire francais -----------------------------
** on devrait peut etre ici gerer le define de ROOT et ROOT_SIZE
**	(qui devrait peut etre s'appeler LINE) plutot que dans le corewar.h ????
**	recupère	dump :
** Au bout de nbr_cycles cycles d’exécution, dump la mémoire sur la sortie
** standard,puis quitte la partie. (mémoire dumpée au format hexadécimal)
** avec 32 octets par ligne.
********************************************************************************
*/

int		get_dump(t_corevm *vm, int i)
{
	if (!ft_strequ(vm->argv[i], "-b"))
		vm->octet_line_viz = 32;
	else
		i++;
	if ((!(ft_strisall(vm->argv[i], &ft_isdigit)))\
		|| (ft_strlen(vm->argv[i]) > 10 || (ft_strlen(vm->argv[i]) == 10\
			&& ft_strcmp(vm->argv[i], "2147483647") > 0)))
		ft_error(vm, ERR_MESS_2, 0);
	vm->dump = ft_atoi(vm->argv[i]);
	return (i);
}

/*
********************************************************************************
** parse_argv manages options (dump, visu, number of player)
** -------------------------- commentaire francais -----------------------------
** parsing des champions (et 2 options : -dump (lié a nbr_cycle) et -visu)
********************************************************************************
*/

void	parse_argv(t_corevm *vm)
{
	int	i;

	i = 0;
	while (vm->argv[++i])
	{
		if (ft_strequ(vm->argv[i], "-dump") && vm->dump == -1)
			i = get_dump(vm, ++i);
		else if (ft_strequ(vm->argv[i], "-viz"))
			vm->viz = 1;
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
	if (vm->viz)
		vm->dump = -1;
}
