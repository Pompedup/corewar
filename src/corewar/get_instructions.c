/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_instructions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 17:22:55 by ccoupez           #+#    #+#             */
/*   Updated: 2018/09/24 17:09:40 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_ptr_func g_instruc_func[] =
{
	{&ft_live, 0x01}, {&ft_ld, 0x02}, {&ft_st, 0x03}, {&ft_add, 0x04},
	{&ft_sub, 0x05}, {&ft_and, 0x06}, {&ft_or, 0x07}, {&ft_xor, 0x08},
	{&ft_zjmp, 0x09}, {&ft_ldi, 0x0a}, {&ft_sti, 0x0b}, {&ft_fork, 0x0c},
	{&ft_lld, 0x0d}, {&ft_lldi, 0x0e}, {&ft_lfork, 0x0f}, {&ft_aff, 0x010},
	{NULL, 0}
};

/*
** add - sub - live - zjmp - fork - lfork - aff (les simples 0 option pour les arg)
** combinaison ok : ld - st - ldi - sti - lld - lldi
** combinaison ok : and - or - xor meme combinaison possible
*/

void	execute_instruction(t_corevm *vm, t_process *actual)
{
	int	i;

	i = 0;
	while (g_op_tab[i].id != 0)
	{
		if (g_op_tab[i].id == actual->type_instruc[0])
		{
			printf("g_op_tab[i].ptrfunc(vm, actual); %d \n", actual->type_instruc[0]);
			g_instruc_func[i].ptrfunc(vm, actual);
			i = 0;
			while (i < 5)
				actual->type_instruc[i++] = -1;
			return ;
		}
		i++;
	}
}

/*
# define REG_CODE	1
# define DIR_CODE	2
# define IND_CODE	3
** pour connaitre le type de notre argument on a 1 octet qui nous indique :
** si l'arg et un registre -> 01 - codé sur 1 octet
** si l'arg et un direct -> 10 - codé sur 2 ou 4 octets
** si l'arg et un indirect -> 11 - codé 2 octets
** ce qui donne avec un mask comme on applique dans la fonction ci dessous
** : 1 pour reg, 2 pour direct ou 3 pour un indirect
** r2,23,%34 donne l’octet de codage 0b 01 11 10 00, soit 0x78
**                                      re id di les 2 derniers bits tjr a 00
*/

void	get_instruction_type(t_corevm *vm, t_process *actual)
{
	int i;

	i = 0;
	while (g_op_tab[i].id != (vm->core[actual->pc % MEM_SIZE]))
		i++;
	if (g_op_tab[i].id == 0)
		return ; //return et je continue la partie voir si on avance le pc ou nn
	actual->nb_cycle_instruc = g_op_tab[i].nb_cycle_instruction;
	actual->type_instruc[0] = g_op_tab[i].id;
	actual->pc++;
	if (g_op_tab[i].nbr_arg > 1)
	{
		actual->type_instruc[1] = vm->core[actual->pc++ % MEM_SIZE];
		//actual->pc++;
	}


}


/*
** je regarde si j'ai deja lu linstruction ou se situe mon pc
** si NON : je la recupere avec get_instruction
** si OUI : je regarde si on est arrive a la fin de son dernier cycle
** pour voir si on peut lexecuter ou non
*/

void	manage_instruction(t_corevm *vm, t_process *process)
{

	if (process->type_instruc[0] == -1)
		get_instruction_type(vm, process);
	else
	{
		process->nb_cycle_instruc--;
		if (process->nb_cycle_instruc == 1)
			execute_instruction(vm, process);
	}
	//execute_instruction(vm, process);
}


/*
** si l'arg et un registre -> 01 - codé sur 1 octet
** si l'arg et un direct -> 10 - codé sur 2 ou 4 octets
** si l'arg et un indirect -> 11 - codé 2 octets


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

{T_REG, T_REG, T_DIR} -> 58  size  process->pc += 6;
{T_REG, T_REG , T_REG} -> 54  size  process->pc += 5;

{T_REG, T_DIR, T_DIR } -> 68  size  process->pc += 7;
{T_REG, T_DIR, T_REG} -> 64  size  process->pc += 6;

{T_REG, T_IND, T_DIR } -> 78  size  process->pc += 7;
{T_REG, T_IND, T_REG} -> 74  size  process->pc += 6;

*/
