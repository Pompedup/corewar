/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecesari <ecesari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 12:02:04 by ccoupez           #+#    #+#             */
/*   Updated: 2018/09/24 12:29:49 by ecesari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** ajoute un joueur (avec un numero)
*/

void	add_player_with_num(t_corevm *vm, int i)
{
	int j;
	int num;

	j = 0;
	if (!(ft_strisall(vm->argv[i + 1], &ft_isdigit))) //verifier que vm->argv[i] est un int
		ft_error(vm, 111); // -n veut un num apres
	num = ft_atoi(vm->argv[i + 1]);
	if (num == 0 || !unused_num(vm, num))
		ft_error(vm, 15); //un joueur ne peux pas avoir le num 0 ou un num deja assigné
	if (ft_strlen(vm->argv[i + 2]) < 4 || !ft_strstr(vm->argv[i + 2], ".cor\0"))
		ft_error(vm, 12); //le fichier champion nest pas bon
	create_player(vm, num, i + 2);
}

/*
** ajoute un joueur (sans numero pour le moment)
*/

void	add_player(t_corevm *vm, int i)
{
	if (ft_strlen(vm->argv[i]) < 4 && !ft_strstr(vm->argv[i], ".cor\0"))
		ft_error(vm, 1); //le nom du fichier champion nest pas bon!!
	create_player(vm, 0, i);
}

/*
** recupère	dump :
** Au bout de nbr_cycles cycles d’exécution, dump la mémoire sur la sortie standard,
** puis quitte la partie. (mémoire dumpée au format hexadécimal)
** avec 32 octets par ligne.
*/

void	get_dump(t_corevm *vm, int i)
{
	// int		j;

	// j = 0;
	// while (ft_isdigit(vm->argv[i][j]) && vm->argv[i][j])
	// 	j++;
	// if (vm->argv[i][j] != '\0')
	// 	ft_error(vm, 110); // usage: ./corewar [-dump nbr_cycles] [[-n number] champion1.cor] ...
	if (!(ft_strisall(vm->argv[i], &ft_isdigit))) //verifier que vm->argv[i] est un int
		ft_error(vm, 111); //  usage: ./corewar [-dump nbr_cycles] [[-n number] champion1.cor] ...
	if ((!(vm->dump = ft_atoi(vm->argv[i]))))
		ft_error(vm, -1); //le nombre de dump doit etre strictement superieur à 0
}

/*
** parsing des champions (et 2 options : -dump (lié a nbr_cycle) et -visu)
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
		else if (ft_strstr(vm->argv[i], ".cor\0")) //
			add_player(vm, i);
		else if (ft_strequ(vm->argv[i], "-n"))
		{
			add_player_with_num(vm, i);
			i += 2;
		}
		else
			ft_error(vm, 8); // usage: ./corewar [-dump nbr_cycles] [[-n number] champion1.cor] ...
		if (vm->info->nb_players > MAX_PLAYERS)
			ft_error(vm, 7); //num error Too many players for the battle :O!!
	}
	if (vm->info->nb_players < 1)
		ft_error(vm, 77); //num error il faut au moins 1 joueurs!!
}
