/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_instructions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 17:22:55 by ccoupez           #+#    #+#             */
/*   Updated: 2018/09/03 18:36:57 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_op    g_op_tab[] =
{
	{"live",  1, {T_DIR}, 1, 10, "alive", 0, 0},
	{"ld",    2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
	{"st",    2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
	{"add",   3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub",   3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
	{"and",   3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or",    3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor",   3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp",  1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
	{"ldi",   3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1},
	{"sti",   3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1},
	{"fork",  1, {T_DIR}, 12, 800, "fork", 0, 1},
	{"lld",   2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
	{"lldi",  3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load 	index",1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
	{"aff",   1, {T_REG}, 16, 2, "aff", 1, 0},
	{0, 0, {0}, 0, 0, 0, 0, 0},
};

//int		get_intruction(t_corevm *vm, t_process *actual)
int		get_intruction(int num)
{
	int i;

	i = 0;
	//while (g_op_tab[i]->id != vm->core[actual->pc % MEM_SIZE])
	while (g_op_tab[i].id != num)
		i++;
	return (i);
}

/*
t_func opcode_tab[] =
{
	{&live, 0x01}, {&ld, 0x02}, {&st, 0x03}, {&add, 0x04}, {&sub, 0x05},
	{&and, 0x06}, {&or, 0x07}, {&xor, 0x08}, {&zjmp, 0x09}, {&ldi, 0x0a},
	{&sti, 0x0b}, {&fork, 0x0c}, {&lld, 0x0d}, {&lldi, 0x0e}, {&lfork, 0x0f},
	{&aff, 0x010}, {NULL, 0}
}
*/

/*int		get_type_first_arg(int num)
{
	return (num >> 6 & 3); //return 1 (reg), 2 (direct) ou 3 (indirect)
}

int		get_type_second_arg(int num)
{
	return (num >> 4 & 3);//return 1 (reg), 2 (direct) ou 3 (indirect)
}

int		get_type_third_arg(int num)
{
		return (num >> 2 & 3);//return 1 (reg), 2 (direct) ou 3 (indirect)
}*/

/*
** pour connaitre le type de notre argument on a 1 octet qui nous indique :
** si l'arg et un registre -> 01
** si l'arg et un direct -> 10
** si l'arg et un indirect -> 11
** ex : r2,23,%34 donne l’octet de codage 0b 01 11 10 00, soit 0x78
**                                           re id di les 2 derniers bits tjr a 00
*/
