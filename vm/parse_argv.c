/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 12:02:04 by ccoupez           #+#    #+#             */
/*   Updated: 2018/07/20 16:37:15 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <fcntl.h>

/*
** ajoute un joueur (avec un numero)
*/

void	add_player_with_num(t_corevm *vm, int i)
{
	int j;
	int num;

	j = 0;
	while (ft_isdigit(vm->argv[i + 1][j]) && vm->argv[i + 1][j])
		j++;
	if (vm->argv[i + 1][j] != '\0')
		ft_error(vm, 1); // -n veut un num apres (1-4)
	num = ft_atoi(vm->argv[i + 1]);
	if ((num < 1 || num > MAX_PLAYERS) || !unused_num(vm, num))
		ft_error(vm, 15); //le num dun joueur doit etre 1 et 4 et sans doublon	
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
	if (vm->info_players->nb_players + 1 > MAX_PLAYERS)
		ft_error(vm, 5); //num error il y a trop de joueur!!
	create_player(vm, 0, i);
}

/*
** recupère	dump : Au bout de nbr_cycles cycles d’exécution,
** dump la mémoire sur la sortie standard,
** puis quitte la partie. La mémoire doit être dumpée au format hexadécimal,
** avec 32 octets par ligne.
*/

void	get_dump(t_corevm *vm, int i)
{
	int		j;

	j = 0;
	while (ft_isdigit(vm->argv[i + 1][j]) && vm->argv[i + 1][j])
		j++;
	if (vm->argv[i + 1][j] != '\0')
		ft_error(vm, 0); // usage: ./corewar [-dump nbr_cycles] [[-n number] champion1.cor] ...
	vm->dump = ft_atoi(vm->argv[i + 1]);
}

/*
** parsing de argv (2 option -dump	qui est lié a nbr_cycle et -visu )
** et 2 manieres de recup les joueurs
** (soit ils ont choisi un num soit la machine leur en attribura un plus tard)
*/

void	parse_argv(t_corevm *vm)
{
	int	i;

	i = 1;
	while (vm->argv[i])
	{
		if (ft_strequ(vm->argv[i], "-dump"))
		{
			get_dump(vm, i);
			i++;
		}
		else if (ft_strequ(vm->argv[i], "-visu"))
			vm->visu = 1;
		else if (ft_strstr(vm->argv[i], ".cor\0"))
			add_player(vm, i);
		else if (ft_strequ(vm->argv[i], "-n"))
		{
			add_player_with_num(vm, i);
			i += 2;
		}
		else
			ft_error(vm, 8); // usage: ./corewar [-dump nbr_cycles] [[-n number] champion1.cor] ...
		if (vm->info_players->nb_players > MAX_PLAYERS)
			ft_error(vm, 7); //num error il y a trop de joueur!!
		i++;
	}
}
