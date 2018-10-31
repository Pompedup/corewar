/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecesari <ecesari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 12:02:04 by ccoupez           #+#    #+#             */
/*   Updated: 2018/10/31 13:38:17 by ecesari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
********************************************************************************
**	init_octet_line_viz helps define the width of viz on the standard output
********************************************************************************
*/

void	init_octet_line_viz(t_corevm *vm)
{
	if (vm->viz || vm->viz_debug)
	{
		vm->dump = -1;
		vm->octet_line_viz = ft_sqrt(MEM_SIZE);
	}
}

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


int		get_viz(t_corevm *vm, int i)
{
	// while (vm->argv[i])
	// {
		if (ft_strequ(vm->argv[i + 1], "-debug"))
		{
			vm->viz_debug = 1;
			i++;
		}
		else
			vm->viz = 1;
		// i++;
	// }
	return (i);
}

/*
********************************************************************************
**	get_dump checks that the number of cycles given is a positive int
**	two options are possible
**	-b to have a larger width displayed (64 bytes instead of 32)
**	-c to display colors
********************************************************************************
*/

int		get_dump(t_corevm *vm, int i)
{
	if (!vm->argv[i])
		ft_error(vm, ERR_MESS_3, 0);
	while (((!(ft_strisall(vm->argv[i], &ft_isdigit)))\
		|| (ft_strlen(vm->argv[i]) > 10 || (ft_strlen(vm->argv[i]) == 10\
		&& ft_strcmp(vm->argv[i], "2147483647") > 0))) && vm->argv[i + 1])
	{
		if (ft_strequ(vm->argv[i], "-b"))
		{
			vm->octet_line_viz = ft_sqrt(MEM_SIZE);
			i++;
		}
		else if (ft_strequ(vm->argv[i], "-c"))
		{
			vm->dump_color = ft_strequ(vm->argv[i], "-c");
			i++;
		}
		else
			ft_error(vm, ERR_MESS_3, 0);
	}
	if ((!(ft_strisall(vm->argv[i], &ft_isdigit)))\
		|| (ft_strlen(vm->argv[i]) > 10 || (ft_strlen(vm->argv[i]) == 10\
		&& ft_strcmp(vm->argv[i], "2147483647") > 0)))
		ft_error(vm, ERR_MESS_2, 0);
	vm->dump = ft_atoi(vm->argv[i]);
	return (i);
}

/*
********************************************************************************
** parse_argv manages options (dump, viz, number of player)
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
			i = get_viz(vm, i);
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
	init_octet_line_viz(vm);
}
