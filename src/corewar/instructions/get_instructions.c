/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_instructions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 17:22:55 by ccoupez           #+#    #+#             */
/*   Updated: 2018/09/03 21:06:02 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

//int		get_intruction(t_corevm *vm, t_process *actual)
int		get_intruction(int num)
{
	extern t_op	*g_op_tab;
	int			i;

	i = 0;
	//while (g_op_tab[i]->id != vm->core[actual->pc % MEM_SIZE])
	while (g_op_tab[i]->id != num)
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
