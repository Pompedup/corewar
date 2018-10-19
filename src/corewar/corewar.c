/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 13:17:29 by ccoupez           #+#    #+#             */
/*   Updated: 2018/10/19 13:15:58 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
********************************************************************************
**	check_include aims at protecting corewar against inccorrect defines in
**	common.h (for MEM_SIZE that must be a multiple of 1024,
**	REG_NUMBER must be in a single)
********************************************************************************
*/

int		check_include(void)
{
	long long	inc;
	int			nb_one;

	inc = 1;
	nb_one = 0;
	if (!MEM_SIZE && MEM_SIZE > SHORT && REG_NUMBER > UNSIGNED_CHAR)
		return (0);
	while (inc < SHORT && inc <= MEM_SIZE)
	{
		if ((MEM_SIZE & inc) != 0)
			nb_one++;
		inc = inc * 2;
	}
	if (nb_one != 1)
		return (0);
	return (1);
}

/*
********************************************************************************
**
********************************************************************************
*/

void	declare_winner(t_corevm *vm)
{
	int			i;
	int			last_live;
	t_player	*winner;

	last_live = 0;
	i = 0;
	while (i < vm->info->nb_players - 1)
	{
		if (vm->lives_player[i][2] < vm->lives_player[i + 1][2])
			last_live = i + 1;
		i++;
	}
	winner = vm->info->first_player;
	while (winner)
	{
		if (winner->num == vm->lives_player[last_live][0])
		{
			ft_printf("le joueur %d(%s) a gagne\n",
				vm->lives_player[last_live][0], winner->header->prog_name);
			return ;
		}
		winner = winner->next;
	}
}

/*
********************************************************************************
** 						(ง •̀_•́)ง  ᕙ༼*◕_◕*༽ᕤ
********************************************************************************
*/

int		main(int ac, char **av)
{
	t_corevm	vm;

	if (ac < 2)
		ft_error(&vm, ERR_MESS_0, 0);
	if (!check_include())
		ft_error(&vm, ERR_MESS_00, 0);
	init_vm(av, &vm);
	parse_argv(&vm);
	number_players(&vm);
	players_charged_in_core(&vm);
	execute_the_battle(&vm);
	declare_winner(&vm);
	return (0);
}
