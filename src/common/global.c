/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecesari <ecesari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 21:06:11 by abezanni          #+#    #+#             */
/*   Updated: 2018/09/24 15:04:33 by ecesari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "corewar.h"

t_op	g_op_tab[] =
{
	{"live",  1, {T_DIR}, 1, 10, "alive", 											0, 0, &ft_live},
	{"ld",    2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 								1, 0, &ft_ld},
	{"st",    2, {T_REG, T_IND | T_REG}, 3, 5, "store", 							1, 0, &ft_st},
	{"add",   3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 							1, 0, &ft_add},
	{"sub",   3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 						1, 0, &ft_sub},
	{"and",   3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et", 																		1, 0, &ft_and},
	{"or",    3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou", 																		1, 0, &ft_or},
	{"xor",   3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"xou", 																		1, 0, &ft_xor},
	{"zjmp",  1, {T_DIR}, 9, 20, "jump if zero", 									0, 1, &ft_zjmp},
	{"ldi",   3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 																1, 1, &ft_ldi},
	{"sti",   3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 																1, 1, &ft_sti},
	{"fork",  1, {T_DIR}, 12, 800, "fork", 											0, 1, &ft_fork},
	{"lld",   2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 						1, 0, &ft_lld},
	{"lldi",  3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load 	index",															1, 1, &ft_lldi},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 									0, 1, &ft_lfork},
	{"aff",   1, {T_REG}, 16, 2, "aff", 											1, 0, &ft_aff},
	{0, 0, {0}, 0, 0, 0, 0, 0, 0},
};
