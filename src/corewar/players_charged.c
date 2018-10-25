/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   players_charged.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecesari <ecesari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 13:36:25 by ccoupez           #+#    #+#             */
/*   Updated: 2018/10/25 11:46:19 by ecesari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"


/*
********************************************************************************
**
			// ft_printf("* le champion n°%d, nommé \033[38;2;%d;%d;%dm%s et pesant %d bytes (%s)\n",\
			ft_printf("* le champion n°%d, nommé \033[38;2;%d;%d;%dm%s%s et pesant %d bytes (%s)\n",
	ft_printf("\t  numéro\tnom du champion\t\tpoids du champion\tcommentaires\n");
			ft_printf("\t* %d,\t\t%s%d;%d;%dm%s%s\t\t\t%d bytes\t\t\"%s\"\n",
	ft_printf("\t  numéro\tnom du champion\t\tpoids du champion\tcommentaires\n");
********************************************************************************
*/

void	introducing_contestants(t_corevm *vm)
{
	t_player		*player_to_introduce;

	player_to_introduce = vm->info->first_player;
	ft_printf("%s%s%s%s%s%s%s\n", LN_32, LN_32, LN_32, LN_32, LN_32, LN_32, LN_15);
	ft_printf("Nous avons le plaisir de vous présenter le combat entre ...\n");
	while (player_to_introduce)
	{
		if (player_to_introduce)
		{
		// ft_printf("vm->tab_color[player_to_introduce->color] hexa %x int %d \n", vm->tab_color[player_to_introduce->color], vm->tab_color[player_to_introduce->color]);
		// ft_printf("vm->tab_color[player_to_introduce->color] hexa %x int %d >> 16) & 0xff\n", (vm->tab_color[player_to_introduce->color] >> 16) & 0xff, (vm->tab_color[player_to_introduce->color] >> 16) & 0xff);
		// ft_printf("vm->tab_color[player_to_introduce->color] hexa %x int %d >> 8) & 0xff\n", (vm->tab_color[player_to_introduce->color] >> 8) & 0xff, (vm->tab_color[player_to_introduce->color] >> 8) & 0xff);
		// ft_printf("vm->tab_color[player_to_introduce->color] hexa %x int %d) & 0xff\n", (vm->tab_color[player_to_introduce->color]) & 0xff, (vm->tab_color[player_to_introduce->color]) & 0xff);
			ft_printf("	* le champion n°%d, nommé %s%d;%d;%dm%s%s et pesant %d bytes (%s)\n",
			(player_to_introduce->num > 0 ? player_to_introduce->num : -player_to_introduce->num), COLOR_LET_ON,
			(vm->tab_color[player_to_introduce->color] >> 16) & 0xff,
			(vm->tab_color[player_to_introduce->color] >> 8) & 0xff,
			(vm->tab_color[player_to_introduce->color]) & 0xff,
			player_to_introduce->header->prog_name, COLOR_OFF,
			player_to_introduce->header->prog_size,
			player_to_introduce->header->comment);
/*ft_printf("* le champion n°%d, nommé %s et pesant %d bytes (%s)\n",\
player_to_introduce->num, player_to_introduce->header->prog_name,\
player_to_introduce->header->prog_size,\
player_to_introduce->header->comment);*/
		}
		player_to_introduce = player_to_introduce->next;
	}
	ft_printf("%s%s%s%s%s%s%s\n", LN_32, LN_32, LN_32, LN_32, LN_32, LN_32, LN_15);
}

/*
********************************************************************************
**	players_charged_in_core transfers players into processes
**	i will be the index in core (relative position of every player in core)
**	place takes on values from 0 to nb->players
********************************************************************************
*/

void	players_charged_in_core(t_corevm *vm)
{
	int			i;
	int			j;
	float		place;
	t_player	*player;

	place = 0;
	player = vm->info->first_player;
	while (player)
	{
		i = ((place / (float)vm->info->nb_players) * (float)MEM_SIZE);
		create_process(vm, i, player);
		j = -1;
		while (++j < player->len_process)
		{
			vm->core[i] = player->process[j];
			if (i != vm->info->first_processus->pc)
				vm->color[i] = vm->info->first_processus->color;
			else if (i == vm->info->first_processus->pc)
				vm->color[i] = vm->info->first_processus->color + 8;
			i++;
		}
		place += 1;
		player = player->next;
	}
	init_lives_player(vm);
}
