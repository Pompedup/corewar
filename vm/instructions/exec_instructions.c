/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_instructions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 14:12:04 by ccoupez           #+#    #+#             */
/*   Updated: 2018/07/20 14:12:15 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

/*
** pour connaitre le type de notre argument on a 1 octet qui nous indique :
** si l'arg et un registre -> 01
** si l'arg et un direct -> 10
** si l'arg et un indirect -> 11
** ex : r2,23,%34 donne l’octet de codage 0b 01 11 10 00, soit 0x78
**                                           re id di les 2 derniers bits tjr a 00
*/


t_func instruction_tab[] =
{
	{&live, 1}, {&ld, 2}, {&st, 3}, {&add, 4}, {&sub, 5}, {&and, 6}, {&or, 7},
	{&xor, 8}, {&zjmp, 9}, {&ldi, 10}, {&sti, 11}, {&fork, 12}, {&lld, 13},
	{&lldi, 14}, {&lfork, 15}, {&aff, 16}, {NULL, 0}
}