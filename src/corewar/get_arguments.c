/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arguments.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 15:16:23 by ccoupez           #+#    #+#             */
/*   Updated: 2018/09/18 18:02:33 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	get_one_octet(t_corevm *vm, t_process *process, int i)
{
	process->args[i] = *(vm->core + (process->pc % MEM_SIZE));
	process->pc += 1;
	printf("arg 1 octet %x\n", process->args[i]);
}

void	get_two_octets(t_corevm *vm, t_process *process, int i)
{
	process->args[i] = *((unsigned short*)(vm->core + (process->pc % MEM_SIZE)));
	ft_memrev((char*)&process->args[i], 2);
	process->pc += 2;
	printf("arg 2 octets %x\n", process->args[i]);
}

void	get_four_octets(t_corevm *vm, t_process *process, int i)
{
	process->args[i] = *((int*)(vm->core + (process->pc % MEM_SIZE)));
	ft_memrev((char*)&process->args[i], 4);
	process->pc += 4;
	printf("arg 4 octets %x\n", process->args[i]);
}


/*
** recupere les arguments pour les fonctions and or et xor
** ca fait un peu foret de fi dsll donc peut etre a opti
** teste toute les possibilites de type pour chaque args
** et ca avamce le pc dans les fonctions get_octets ci dessus !!
*/

void	get_args_and_or_xor(t_corevm *vm, t_process *process)
{
	static unsigned int	key_tab[9] =
		{0x54, 0x74, 0x64, 0x94, 0xb4, 0xa4, 0xd4, 0xf4, 0xe4};

	if (process->type_instruc[1] == 0x54 || process->type_instruc[1] == 0x74
		|| process->type_instruc[1] == 0x64)
		get_one_octet(vm, process, 0);
	else if (process->type_instruc[1] == 0xd4 || process->type_instruc[1] == 0xf4
		|| process->type_instruc[1] == 0xe4)
		get_two_octets(vm, process, 0);
	else if (process->type_instruc[1] == 0x94 || process->type_instruc[1] == 0xb4
		|| process->type_instruc[1] == 0xa4)
		get_four_octets(vm, process, 0);


	if (process->type_instruc[1] == 0x54 || process->type_instruc[1] == 0x94
		|| process->type_instruc[1] == 0xd4)
		get_one_octet(vm, process, 1);
	else if (process->type_instruc[1] == 0x74 || process->type_instruc[1] == 0xb4
		|| process->type_instruc[1] == 0xf4)
		get_two_octets(vm, process, 1);
	else if (process->type_instruc[1] == 0x64 || process->type_instruc[1] == 0xa4
		|| process->type_instruc[1] == 0xe4)
		get_four_octets(vm, process, 1);

	if (is_in_key_tab(process->type_instruc[1], key_tab, 9))
		get_one_octet(vm, process, 2);
}


void	get_args_ldi_lldi(t_corevm *vm, t_process *process)
{
		unsigned int	key_tab[6]= {0x64, 0x54, 0xa4, 0x94, 0xe4, 0xd4};

	if (process->type_instruc[1] == 0x64 || process->type_instruc[1] == 0x54)
		get_one_octet(vm, process, 0);
	else if (is_in_key_tab(process->type_instruc[1], key_tab + 2, 4))
		get_two_octets(vm, process, 0);

	if (process->type_instruc[1] == 0x54 || process->type_instruc[1] == 0x94
		|| process->type_instruc[1] == 0xd4)
		get_one_octet(vm, process, 1);
	if (process->type_instruc[1] == 0x64 || process->type_instruc[1] == 0xa4
		|| process->type_instruc[1] == 0xe4)
		get_two_octets(vm, process, 1);

	if (is_in_key_tab(process->type_instruc[1], key_tab, 6))
		get_one_octet(vm, process, 3);
}
