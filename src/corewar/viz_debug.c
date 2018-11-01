/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viz_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecesari <ecesari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 11:51:31 by ccoupez           #+#    #+#             */
/*   Updated: 2018/11/01 14:14:42 by ecesari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
********************************************************************************
**	get_viz helps correctly parse argv
********************************************************************************
*/

int		get_viz(t_corevm *vm, int i)
{
	if (ft_strequ(vm->argv[i + 1], "-debug"))
	{
		vm->viz_debug = 1;
		vm->viz = 0;
		i++;
	}
	else if (!vm->viz_debug)
		vm->viz = 1;
	return (i);
}

/*
********************************************************************************
**	to_define_color was created to help with the norm
********************************************************************************
*/

void	to_define_color(t_corevm *vm, t_process *tmp)
{
	tmp->live = -1;
	if (vm->color[tmp->pc & (MEM_SIZE - 1)] == 12)
		vm->color[tmp->pc & (MEM_SIZE - 1)]++;
	else if (vm->color[tmp->pc & (MEM_SIZE - 1)] > 7\
	&& vm->color[tmp->pc & (MEM_SIZE - 1)] != 13)
		vm->color[tmp->pc & (MEM_SIZE - 1)] -= 8;
}

/*
********************************************************************************
**	who_still_lives
********************************************************************************
*/

void	who_still_lives(t_corevm *vm)
{
	int			i;
	t_process	*tmp;

	tmp = vm->info->first_processus;
	i = 0;
	while (i < vm->info->nb_players)
		vm->lives_player[i++][3] = 0;
	while (tmp)
	{
		i = 0;
		while (i < vm->info->nb_players
		&& tmp->num_player != vm->lives_player[i][0])
			i++;
		if (tmp->num_player == vm->lives_player[i][0]\
		&& !vm->lives_player[i][1] && tmp->live < 1)
			to_define_color(vm, tmp);
		else
			tmp->live = 0;
		if (tmp->live > -1)
			vm->lives_player[i][3] = 1;
		tmp = tmp->next;
	}
}

/*
********************************************************************************
**	viz_debug enables the input of a number of cycle to forwar to
********************************************************************************
*/

void	viz_debug(t_corevm *vm, int *debug)
{
	char	*line;

	if (vm->nbr_total_cycles > CYCLE_DEBUG + *debug)
	{
		ft_printf(CLEAR);
		print_header_viz(vm);
		print_introduction(vm);
		print_core(vm);
		print_summary(vm);
		while (get_next_line(0, &line) == 0)
			if (*line == 'q')
			{
				free_vm(vm);
				exit(0);
			}
		*debug += ft_atoi(line);
		free(line);
	}
}
