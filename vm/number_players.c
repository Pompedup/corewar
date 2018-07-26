/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_players.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 15:56:15 by ccoupez           #+#    #+#             */
/*   Updated: 2018/07/26 15:36:55 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		unused_num(t_corevm *vm, int num)
{
	int			i;
	t_player	*tmp;

	i = 0;
	tmp = vm->info_players->first;
	while (tmp && i++ < MAX_PLAYERS)
	{
		if (num == tmp->num)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

/*
** je met les joueurs dans l'ordre croissant pour bien les placer dans l'arenne
*/

void	sort_players(t_corevm *vm)
{
	t_player	*prev;
	t_player	*actual;
	t_player	*new;

	prev = NULL;
	actual = vm->info_players->first;
	while (actual->next)
	{
		if (actual->num > actual->next->num)//je me suis peut etre tromper dans l'ordre alors (croissant ou decroissant)??!! < > ?
		{
			new = actual->next;
			if (actual == vm->info_players->first)
				vm->info_players->first = new;
			else
				prev->next = new;
			actual->next = new->next;
			new->next = actual;
			actual = vm->info_players->first;
		}
		else
		{
			prev = actual;
			actual = actual->next;
		}
	}
}

/*
** ????
** Le numéro du joueur est généré par la machine ou spécifié au lancement, et est
** fourni aux champions via le registre r1 (???) de leur premier processus au démarrage.
** Tous les autres registres sont mis à 0. Sauf le PC.
** ????
*/

/*
** j'assigne un num a tout les joueurs qui en on pas et les trie (en commencant par 1 obligatoirement) !!
** !!!! ds le sujet --> le dernier né joue en premier.
** je me suis peut etre tromper dans l'ordre alors (croissant ou decroissant)??!!
*/

void	number_players(t_corevm *vm)
{
	int			i;
	t_player	*tmp;

	tmp = vm->info_players->first;
	while (tmp)
	{
		if (tmp->num == 0)
		{
			i = 1;
			while (!(unused_num(vm, i)))
				i++;
			tmp->num = i;
			tmp->reg[0] = i; //* voir 2 commentaires au dessus pour voir a quoi ca sert cette ligne
		}
		tmp = tmp->next;
	}
	sort_players(vm);
	tmp = vm->info_players->first;
	tmp->num = 0;
	while (tmp->next)
	{
		if (tmp->next->num != tmp->num + 1)
			tmp->next->num = tmp->num + 1;
		tmp = tmp->next;
	}
}
