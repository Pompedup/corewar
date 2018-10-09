/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_instructions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 17:22:55 by ccoupez           #+#    #+#             */
/*   Updated: 2018/10/09 14:23:08 by ccoupez          ###   ########.fr       */
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
** add - sub - live - zjmp - fork - lfork - aff (les simples 0 option pour les arg)
** combinaison ok : ld - st - ldi - sti - lld - lldi
** combinaison ok : and - or - xor meme combinaison possible
********************************************************************************
*/

int		execute_instruction(t_corevm *vm, t_process *process)
{
	int	i;

	i = 0;
	if (vm->nbr_total_cycles > CYCLE_DEBUG)
		ft_printf(" execute i process->type_instruc[0] hexa %x\n", process->type_instruc[0]);
	// ft_printf(" g_op_tab[process->type_instruc[0]].shortcut %s\n", g_op_tab[process->type_instruc[0]].shortcut);
	if (!(g_instruc_func[process->type_instruc[0]].ptrfunc(vm, process)))
		return (0);
	i = 0;
	while (i < 2)
		process->type_instruc[i++] = -1;
	return (1);
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
// ft_printf(" dans get_instruction vm->core[process->pc] %x\n", vm->core[process->pc]);
	while (g_op_tab[i].id != (vm->core[process->pc & (MEM_SIZE - 1)]) && g_op_tab[i].id)
		i++;
	if (g_op_tab[i].id == 0)
	{
		ft_printf("no instruction!!!!!!!!!!!\n");
		//process->pc++;
		return ;
	}
	process->pc_tmp++;
	process->nb_cycle_instruc = g_op_tab[i].nb_cycle_instruction;
	process->type_instruc[0] = i;
	if (g_op_tab[i].nbr_arg > 1 || process->type_instruc[0] == 16)
	{
		process->type_instruc[1] = (unsigned char)(vm->core[(process->pc + process->pc_tmp) & (MEM_SIZE - 1)]);
		// ft_printf(" process->type_instruc[1] int %d\n", process->type_instruc[1]);
		// ft_printf(" (vm->core[process->pc & (MEM_SIZE - 1)]) int %d\n", (unsigned char)(vm->core[(process->pc) & (MEM_SIZE - 1)]));
		// ft_printf("process->type_instruc[1] hexa %hhx\n", process->type_instruc[1]);
		// ft_printf("vm->core[process->pc] hexa %x\n", vm->core[process->pc]);
	process->pc_tmp++;
	}
}

/*
********************************************************************************
**	manage_instruction reupere l'instruction et ne l'execute qu'a la fin du cycle
**
** je regarde si j'ai deja lu linstruction ou se situe mon pc
** si NON : je la recupere avec get_instruction
** si OUI : je regard	e si on est arrive a la fin de son dernier cycle
** pour voir si on peut lexecuter ou non
********************************************************************************
*/

void	manage_instruction(t_corevm *vm, t_process *process)
{
// ft_printf("	process->type_instruc[0] %d\n", process->type_instruc[0]);
	if (process->type_instruc[0] == -1)
	{
		ft_printf("process->type_instruc[0] == -1) -------------!\n");
		get_instruction_type(vm, process);
	}
	else
	{
		process->nb_cycle_instruc--;
		// vm->nbr_total_cycles++;
			// ft_putendl("TEST");
		if (vm->nbr_total_cycles > CYCLE_DEBUG)
			ft_printf("	process->nb_cycle_instruc %d\n", process->nb_cycle_instruc);
		if (vm->nbr_total_cycles > CYCLE_DEBUG)
			if (process->type_instruc[0] != -1)
				ft_printf("	fonction '%s'\n", g_op_tab[process->type_instruc[0]].shortcut);
// ft_printf("	nombre total de cycles vm->nbr_total_cycles %d\n", vm->nbr_total_cycles);
		if (process->nb_cycle_instruc == 1)
		{
			// ft_printf("	process->type_instruc[1] %x\n", process->type_instruc[1]);
			if (execute_instruction(vm, process))
			{
				pc_color(vm, process);
				//redevenir normal
				//if (vm->color[process->pc] < 12 && vm->color[process->pc] > 7)
				//	vm->color[process->pc] -= 8;
				//else if (vm->color[process->pc] == 12)
				//	vm->color[process->pc]++;
//
				//process->pc += process->pc_tmp;
				//process->pc_tmp = 0;
//
				////devenir un pc
				//if (vm->color[process->pc] < 8)
				//	vm->color[process->pc] = vm->color[process->pc] < 4 ? vm->color[process->pc] + 8 : vm->color[process->pc] + 4;//pour les cas de fork
				//else if (vm->color[process->pc] == 13)
				//	vm->color[process->pc]--;
//
			}
		}
				// move_pc(process, g_op_tab[process->type_instruc[0]]);
		// ft_printf("sortie\n");
	// execute_instruction(vm, process);
	}
}


/*
** si l'arg et un registre -> 01 - codé sur 1 octet
** si l'arg et un direct -> 10 - codé sur 2 ou 4 octets
** si l'arg et un indirect -> 11 - codé 2 octets



taille live {T_DIR} D4             -> process->pc += 5

taille zjmp {T_DIR} D2             -> process->pc += 3

taille fork  {T_DIR} D2            -> process->pc += 3
taille lfork {T_DIR} D2            -> process->pc += 3

taille aff {T_REG}                -> process->pc += 3

Combinaison pour add - sub :

{T_REG, T_REG, T_REG} ->54  size  process->pc += 5;

________________________________________
Combinaison pour and - or - xor :
{T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}

{T_REG , T_REG , T_REG} -> 54  size  process->pc += 5;
{T_REG , T_IND, T_REG} -> 74  size  process->pc += 6;
{T_REG, T_DIR, T_REG} -> 64 size  process->pc += 8;


{T_DIR , T_REG, T_REG} -> 94  size  process->pc += 8;
{T_DIR, T_IND , T_REG} -> B4  size  process->pc += 9;
{T_DIR, T_DIR, T_REG} -> A4  size  process->pc += 11;

{T_IND, T_REG, T_REG} ->D4  size  process->pc += 6;
{T_IND, T_IND, T_REG} -> F4  size  process->pc += 7;
{T_IND, T_DIR, T_REG} -> E4  size  process->pc += 9;
  11      10    01     00

________________________________________
Combinaison pour ld - lld:
{T_DIR | T_IND, T_REG}

{T_DIR, T_REG} -> 90  size  process->pc += 5;
{T_IND, T_REG} -> D0  size  process->pc += 7;

________________________________________
Combinaison pour st :
{T_REG, T_IND | T_REG}

{T_REG, T_REG} -> 50  size  process->pc += 4;
{T_REG, T_IND} -> 70  size  process->pc += 5;

________________________________________
Combinaison pour ldi - lldi :
{T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}

{T_REG , T_DIR, T_REG} -> 64  size  process->pc += 6;
{T_REG, T_REG, T_REG} -> 54  size  process->pc += 5;

{T_DIR , T_DIR , T_REG} -> A4  size  process->pc += 7;
{T_DIR, T_REG, T_REG} -> 94  size  process->pc += 6;

{T_IND, T_DIR, T_REG} -> E4  size  process->pc += 7;
{T_IND, T_REG, T_REG} -> D4  size  process->pc += 6;

________________________________________
Combinaison pour sti :
{T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}

{T_REG, T_REG, T_DIR} -> 0x58  size  process->pc += 6;
{T_REG, T_REG , T_REG} -> 0x54  size  process->pc += 5;

{T_REG, T_DIR, T_DIR } -> 0x68  size  process->pc += 7;
{T_REG, T_DIR, T_REG} -> 0x64  size  process->pc += 6;

{T_REG, T_IND, T_DIR } -> 0x78  size  process->pc += 7;
{T_REG, T_IND, T_REG} -> 0x74  size  process->pc += 6;

*/
