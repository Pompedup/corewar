/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_players.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecesari <ecesari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 15:56:15 by ccoupez           #+#    #+#             */
/*   Updated: 2018/10/25 19:37:53 by ecesari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
********************************************************************************
**	def_col defines the color to be returned to use in ft_printf
**	created to help with the norm
********************************************************************************
*/

int		def_col(t_corevm *vm, int index, int rgb)
{
	if (rgb == 1)
		return ((vm->tab_color[index] >> 16) & 0xff);
	if (rgb == 2)
		return ((vm->tab_color[index] >> 8) & 0xff);
	if (rgb == 3)
		return ((vm->tab_color[index]) & 0xff);
	return (0);
}

/*
********************************************************************************
**	unused_num returns 0 if num is already used for one of the players
**	or 1 if the num is indeed unused
********************************************************************************
*/

int		unused_num(t_corevm *vm, int num)
{
	int			i;
	t_player	*tmp;

	i = 0;
	tmp = vm->info->first_player;
	while (tmp && i++ < MAX_PLAYERS)
	{
		if (num == tmp->num)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

/*
********************************************************************************
**	number_players gives to each player that did not already had a number
**	the incremented number available starting from 1
**	(only for players created through add_player, meaning num == 0)
********************************************************************************
*/

void	number_players(t_corevm *vm)
{
	int			i;
	t_player	*tmp;

	tmp = vm->info->first_player;
	while (tmp)
	{
		if (tmp->num == 0)
		{
			i = -1;
			while (!(unused_num(vm, i)))
				i--;
			tmp->num = i;
		}
		tmp = tmp->next;
	}
}
