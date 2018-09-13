/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_instructions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 17:22:55 by ccoupez           #+#    #+#             */
/*   Updated: 2018/09/13 17:42:39 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
/*
t_func opcode_tab[] =
{
	{&live, 0x01}, {&ld, 0x02}, {&st, 0x03}, {&add, 0x04}, {&sub, 0x05},
	{&and, 0x06}, {&or, 0x07}, {&xor, 0x08}, {&zjmp, 0x09}, {&ldi, 0x0a},
	{&sti, 0x0b}, {&fork, 0x0c}, {&lld, 0x0d}, {&lldi, 0x0e}, {&lfork, 0x0f},
	{&aff, 0x010}, {NULL, 0}
}
*/

t_op	g_op_tab[] =
{
	{"live",  1, {T_DIR}, 1, 10, "alive", 0, 0, &ft_live},
	{"ld",    2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0, &ft_ld},
	{"st",    2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0, &ft_st},
	{"add",   3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0, &ft_add},
	{"sub",   3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0, &ft_sub},
	{"and",   3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et", 1, 0, &ft_and},
	{"or",    3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou", 1, 0, &ft_or},
	{"xor",   3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"xou", 1, 0, &ft_xor},
	{"zjmp",  1, {T_DIR}, 9, 20, "jump if zero", 0, 1, &ft_zjmp},
	{"ldi",   3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1, &ft_ldi},
	{"sti",   3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1, &ft_sti},
	{"fork",  1, {T_DIR}, 12, 800, "fork", 0, 1, &ft_fork},
	{"lld",   2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0, &ft_lld},
	{"lldi",  3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load 	index",1, 1, &ft_lldi},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1, &ft_lfork},
	{"aff",   1, {T_REG}, 16, 2, "aff", 1, 0, &ft_aff},
	{0, 0, {0}, 0, 0, 0, 0, 0, 0},
};

/*
** add - sub - live - zjmp - fork - lfork - aff (les simples 0 option pour les arg)
** combinaison ok : ld - st - ldi - sti - lld - lldi
** combinaison ok : and - or - xor meme combinaison possible
*/

void	execute_instruction	, t_process *actual)
{
	int	i;

	i = 0;
	while (g_op_tab[i].id != 0)
	{
		if (g_op_tab[i].id == actual->type_instruc[0])
		{
			printf("g_op_tab[i].ptrfunc(vm, actual); %d \n", actual->type_instruc[0]);
			//g_op_tab[i].ptrfunc(vm, actual);
			i = 0;
			while (i < 5)
				actual->type_instruc[i++] = -1;
			return ;
		}
		i++;
	}
	ft_error(vm, 99); //probleme dinstruction
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

void	get_args_type(t_corevm *vm, t_process *actual)
{
	int key;

	key = vm->core[(actual->pc + 1) % MEM_SIZE];
	actual->type_instruc[1] = (key >> 6) & 3;
	actual->type_instruc[2] = (key >> 4) & 3;
	actual->type_instruc[3] = (key >> 2) & 3;
	actual->type_instruc[4] = key & 3; //si ce nest pas == 0 ERREUR !! a checker losquon verifie les arg dans linstruction
}

void	get_instruction_type(t_corevm *vm, t_process *actual)
{
	int i;

	i = 0;
	while (g_op_tab[i].id != (vm->core[actual->pc % MEM_SIZE]))
		i++;
	if (g_op_tab[i].id == 0)
		ft_error(vm, 88); //linstruction nexiste pas
	actual->nb_cycle_instruc = g_op_tab[i].nb_cycle_instruction;
	actual->type_instruc[0] = g_op_tab[i].id;
	if (g_op_tab[i].nbr_arg > 1)
		get_args_type(vm, actual);
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
}


/*

Combinaison pour and - or - xor :

{T_REG , T_REG , T_REG} ->54
{T_REG , T_IND, T_REG} -> 74
{T_REG, T_DIR, T_REG} ->64


{T_DIR , T_REG, T_REG} -> 94
{T_DIR, T_IND , T_REG} -> B4
{T_DIR, T_DIR, T_REG} -> A4

{T_IND, T_REG, T_REG} ->D4
{T_IND, T_IND, T_REG} -> F4
{T_IND, T_DIR, T_REG} -> E4

________________________________________
Combinaison pour ld :

{T_DIR, T_REG} -> 90
{T_IND, T_REG} -> D

________________________________________
Combinaison pour st :

{T_REG, T_REG} -> 50
{T_REG, T_IND} -> 70

________________________________________
Combinaison pour ldi :

{T_REG , T_DIR, T_REG} -> 64
{T_REG, T_REG, T_REG} -> 54

{T_DIR , T_DIR , T_REG} -> A4
{T_DIR, T_REG, T_REG} -> 94

{T_IND, T_DIR, T_REG} -> E4
{ T_IND, T_REG, T_REG} -> D4

________________________________________
Combinaison pour sdi :

{T_REG, T_REG, T_DIR} -> 58
{T_REG, T_REG , T_REG} -> 54

{T_REG, T_DIR, T_DIR } -> 68
{T_REG, T_DIR, T_REG} -> 64

{T_REG, T_IND, T_DIR } -> 78
{T_REG, T_IND, T_REG} -> 74

________________________________________
Combinaison pour lld :

{T_DIR , T_REG} -> 90
{T_IND, T_REG} -> D


________________________________________
Combinaison pour lldi :

{T_REG , T_DIR , T_REG} -> 64
{T_REG, T_REG, T_REG} -> 54

{ T_DIR, T_DIR , T_REG} -> A4
{ T_DIR, T_REG, T_REG} -> 94


{T_IND, T_DIR , T_REG} -> E4
{T_IND, T_REG, T_REG} -> D4


** si l'arg et un registre -> 01 - codé sur 1 octet
** si l'arg et un direct -> 10 - codé sur 2 ou 4 octets
** si l'arg et un indirect -> 11 - codé 2 octets
*/
