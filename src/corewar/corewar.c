/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecesari <ecesari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 13:17:29 by ccoupez           #+#    #+#             */
/*   Updated: 2018/10/19 19:55:34 by ecesari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
********************************************************************************
**	check_include aims at protecting corewar against inccorrect defines in
**	common.h (for MEM_SIZE that must exist and be a multiple of 1024,
**	REG_NUMBER must exist and be in a single char)
**	we reckon that these two defines are the most relevant ones to modify
********************************************************************************
*/

int		check_include(void)
{
	long long	inc;
	int			nb_one;

	inc = 1;
	nb_one = 0;
	if (!MEM_SIZE || MEM_SIZE > SHORT || !REG_NUMBER
	|| REG_NUMBER > UNSIGNED_CHAR)
	{
		ft_fprintf(2, "Error: %s %s.\n", ERR_MESS_00, ERR_MESS_01);
		exit(0);
	}
	while (inc < SHORT && inc <= MEM_SIZE)
	{
		if ((MEM_SIZE & inc) != 0)
			nb_one++;
		inc = inc * 2;
	}
	if (nb_one != 1)
	{
		ft_fprintf(2, "Error: MEM_SIZE is not a multiple of 1024.\n");
		exit(0);
	}
	return (1);
}

/*
********************************************************************************
**	declare_winner concludes corewar and declare the winner
**	the winner is the player that made the last live
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
			ft_printf("Le joueur %d(%s) a gagné\n",
				vm->lives_player[last_live][0], winner->header->prog_name);
			return ;
		}
		winner = winner->next;
	}
}

/*
********************************************************************************
**	These are the rules of corewar:
**	-
**
**
**
** 				let's	(ง •̀_•́)ง  ᕙ༼*◕_◕*༽ᕤ
********************************************************************************
*/

int		main(int ac, char **av)
{
	t_corevm	*vm;

	vm = NULL;
	if (ac < 2)
	{
		ft_fprintf(2, "Error: %s.\n", ERR_MESS_0);
		return (0);
	}
	check_include();
	init_vm(av, vm);
	parse_argv(vm);
	number_players(vm);
	players_charged_in_core(vm);
	execute_the_battle(vm);
	declare_winner(vm);
	free_vm(vm);
	return (0);
}
