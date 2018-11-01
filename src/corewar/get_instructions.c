/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_instructions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecesari <ecesari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 17:22:55 by ccoupez           #+#    #+#             */
/*   Updated: 2018/11/01 13:20:44 by ecesari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
********************************************************************************
**	pointers to functions array linked to the opcode
********************************************************************************
*/

t_ptr_func g_instruc_func[] =
{
	{&ft_live, 0x01}, {&ft_ld, 0x02}, {&ft_st, 0x03}, {&ft_add, 0x04},
	{&ft_sub, 0x05}, {&ft_and, 0x06}, {&ft_or, 0x07}, {&ft_xor, 0x08},
	{&ft_zjmp, 0x09}, {&ft_ldi, 0x0a}, {&ft_sti, 0x0b}, {&ft_fork, 0x0c},
	{&ft_lld, 0x0d}, {&ft_lldi, 0x0e}, {&ft_lfork, 0x0f}, {&ft_aff, 0x010},
	{NULL, 0}
};

/*
********************************************************************************
**	get_pc_tmp enables to forward pc even in case of a wrong key
********************************************************************************
*/

void	get_pc_tmp(t_process *process, t_op g_tab)
{
	int		i;
	char	key;
	int		dec;

	i = 0;
	dec = 6;
	while (i < g_tab.nbr_arg)
	{
		key = (process->type_instruc[1] >> dec) & 3;
		if (key == 1)
			process->pc_tmp++;
		else if (key == 2 && !g_tab.dir)
			process->pc_tmp += 4;
		else if (key == 3 || (key == 2 && g_tab.dir))
			process->pc_tmp += 2;
		dec -= 2;
		i++;
	}
}

/*
********************************************************************************
**	execute_instruction
********************************************************************************
*/

void	execute_instruction(t_corevm *vm, t_process *process)
{
	int	i;

	if (g_op_tab[process->type_instruc[0]].nbr_arg > 1
		|| g_op_tab[process->type_instruc[0]].id == 16)
	{
		process->type_instruc[1] =
			(char)(vm->core[(process->pc + process->pc_tmp) & (MEM_SIZE - 1)]);
		process->pc_tmp++;
	}
	if (!(test_args(process, g_op_tab[process->type_instruc[0]]))
		&& g_op_tab[process->type_instruc[0]].nbr_arg > 1)
		get_pc_tmp(process, g_op_tab[process->type_instruc[0]]);
	else
		g_instruc_func[process->type_instruc[0]].ptrfunc(vm, process);
	i = 0;
	while (i < 2)
		process->type_instruc[i++] = -1;
}

/*
********************************************************************************
**	get_instruction_type
**	in order to know the arg type there is one byte
**	if arg is a register : 01 it will be coded on 1 byte
**	if arg is a direct : 10 it will be coded on either 2 or 4 bytes
**	if arg is an indirect : 11 it will be coded on 2 bytes
**	thanks to a mask it will be 1 for reg, 2 for direct and 3 for indirect
** 	r2,23,%34 will be 0b 01 11 10 00, hence 0x78
**                       re id di (last two bytes always at 0)
********************************************************************************
*/

void	get_instruction_type(t_corevm *vm, t_process *process)
{
	int i;

	i = 0;
	while (g_op_tab[i].id != (vm->core[process->pc & (MEM_SIZE - 1)])
		&& g_op_tab[i].id)
		i++;
	if (g_op_tab[i].id == 0)
	{
		process->pc_tmp++;
		pc_color(vm, process);
		return ;
	}
	process->pc_tmp++;
	process->nb_cycle_instruc = g_op_tab[i].nb_cycle_instruction;
	process->type_instruc[0] = i;
}

/*
********************************************************************************
**	manage_instruction calls get_instruction_type if the type is not already
**	define and otherwise waits for the last nb_cycle_instruc to execute
********************************************************************************
*/

void	manage_instruction(t_corevm *vm, t_process *process)
{
	if (process->type_instruc[0] == -1)
		get_instruction_type(vm, process);
	else
	{
		process->nb_cycle_instruc--;
		if (process->nb_cycle_instruc == 1)
		{
			execute_instruction(vm, process);
			process->good_reg = 1;
			pc_color(vm, process);
		}
	}
}
