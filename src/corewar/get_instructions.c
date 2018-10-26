/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_instructions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecesari <ecesari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 17:22:55 by ccoupez           #+#    #+#             */
/*   Updated: 2018/10/26 13:08:20 by ecesari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	tableau de pointeurs sur fonctions liees a l'opcode
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
** si on a une mauvaise key avancer le pc quand meme en fonction de la key
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
**
********************************************************************************
*/

void	execute_instruction(t_corevm *vm, t_process *process)
{
	int	i;

		ft_printf("	process->type_instruc[0] %x \n", process->type_instruc[0]);
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
	{
		// ft_printf("g_op_tab[process->type_instruc[0] %x \n", g_op_tab[process->type_instruc[0]]);
		ft_printf("execute process->carry %d \n", process->carry);
		g_instruc_func[process->type_instruc[0]].ptrfunc(vm, process);
	}
	i = 0;
	while (i < 2)
		process->type_instruc[i++] = -1;
}

/*
********************************************************************************
**
**	# define REG_CODE	1
**	# define DIR_CODE	2
**	# define IND_CODE	3
** pour connaitre le type de notre argument on a 1 octet qui nous indique :
** si l'arg et un registre -> 01 - codé sur 1 octet
** si l'arg et un direct -> 10 - codé sur 2 ou 4 octets
** si l'arg et un indirect -> 11 - codé 2 octets
** ce qui donne avec un mask comme on applique dans la fonction ci dessous
** : 1 pour reg, 2 pour direct ou 3 pour un indirect
** r2,23,%34 donne l’octet de codage 0b 01 11 10 00, soit 0x78
**                                      re id di les 2 derniers bits tjr a 00
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
**	manage_instruction reupere l'instruc et ne l'execute qu'a la fin du cycle
**
** je regarde si j'ai deja lu linstruction ou se situe mon pc
** si NON : je la recupere avec get_instruction
** si OUI : je regard	e si on est arrive a la fin de son dernier cycle
** pour voir si on peut lexecuter ou non
********************************************************************************
*/

/*
********************************************************************************
**	if (vm->nbr_total_cycles > CYCLE_DEBUG)
**		ft_printf("	process->type_instruc[0] %d\n", process->type_instruc[0]);
**		ft_printf("process->type_instruc[0] == -1) -------------!\n");
**		ft_printf("	process->nb_cycle_instruc %d\n", process->nb_cycle_instruc);
**		ft_printf("fonction %s\n", g_op_tab[process->type_instruc[0]].shortcut);
**		ft_printf("	process->type_instruc[1] %x\n", process->type_instruc[1]);
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
