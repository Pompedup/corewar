/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viz.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecesari <ecesari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 12:24:37 by ecesari           #+#    #+#             */
/*   Updated: 2018/10/25 13:58:04 by ecesari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
********************************************************************************
** print_header_viz
********************************************************************************
*/

void	print_header_viz(t_corevm *vm)
{
	(void)vm;
	ft_printf("%s%s%s%s%s%s%s\n", LN_32, LN_32, LN_32, LN_32, LN_32, LN_32, LN_15);
	// ft_printf("|%s|\n", "COREWAR");
	// ft_printf("%s|\n", (vm->octet_line_viz * 3 + 1)/2, "COREWAR");

	ft_printf("|% -*.*s|\n", (vm->octet_line_viz * 3 + 1), (vm->octet_line_viz * 3 + 1)/2, "COREWAR");
	// ft_printf("%s%s%s%s%s%s%s\n", LN_32, LN_32, LN_32, LN_32, LN_32, LN_32, LN_15);
}

/*
********************************************************************************
** print_introduction
********************************************************************************
*/

void	print_introduction(t_corevm *vm)
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
** print_summary
********************************************************************************
*/

void	print_summary(t_corevm *vm)
{
(void) vm;
}

/*
********************************************************************************
** print_it_all
********************************************************************************
*/

void	print_it_all(t_corevm *vm)
{
	ft_printf(CLEAR);
	print_header_viz(vm);
	print_introduction(vm);
	print_core(vm);
	print_summary(vm);
	sleep(1);

}
