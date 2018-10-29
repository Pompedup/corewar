/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arguments.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecesari <ecesari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 15:16:23 by ccoupez           #+#    #+#             */
/*   Updated: 2018/10/29 19:32:00 by ecesari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
********************************************************************************
**	process->good_reg is set at 0 to handle errors such as an incorrect reg
** -------------------------- commentaire francais -----------------------------
** recupère seulement les registres codés sur 1 octet
********************************************************************************
*/

void	get_one_octet(t_corevm *vm, t_process *process, int i)
{
	process->args[i] =
		*(vm->core + ((process->pc + process->pc_tmp) & (MEM_SIZE - 1))) - 1;
	process->pc_tmp += 1;
	if (process->args[i] < 0 || process->args[i] > REG_NUMBER - 1)
		process->good_reg = 0;
}

/*
********************************************************************************
** -------------------------- commentaire francais -----------------------------
** recupère les indirects et une partie des directs codés sur 2 octets
********************************************************************************
*/

void	get_two_octets(t_corevm *vm, t_process *process, int i)
{
	short tmp;

	tmp = *((short*)(vm->core + ((process->pc + process->pc_tmp)
		& (MEM_SIZE - 1))));
	ft_memrev((char*)&tmp, 2);
	process->args[i] = tmp;
	process->pc_tmp += 2;
}

/*
********************************************************************************
** -------------------------- commentaire francais -----------------------------
** recupère une partie des directs codés sur 4 octets)
**	 ft_printf("vm->core[process->pc] %x\n", vm->core[process->pc]);
**	ft_printf("-------22-------------process->args[i] %d\n", process->args[i]);
**	if (vm->nbr_total_cycles > CYCLE_DEBUG)
**		ft_printf("arg 4 octets %x\n", process->args[i]);
**  ft_printf("get indice %d\n", ((add + j) & (MEM_SIZE - 1)));
**	 ft_printf("get char %d\n", *(vm->core + ((add + j) & (MEM_SIZE - 1))));
********************************************************************************
*/

void	get_four_octets(t_corevm *vm, t_process *process, int i)
{
	int add;
	int	j;

	add = (process->pc + process->pc_tmp) & (MEM_SIZE - 1);
	if (add >= MEM_SIZE - 4)
	{
		j = 0;
		while (j < 4)
		{
			((char *)(&process->args[i]))[j] = *(vm->core + ((add + j)
				& (MEM_SIZE - 1)));
			j++;
		}
	}
	else
	{
		process->args[i] =
			*((int*)(vm->core + ((process->pc + process->pc_tmp)
				& (MEM_SIZE - 1))));
		ft_memrev((char*)&process->args[i], 4);
	}
	process->pc_tmp += 4;
}

/*
********************************************************************************
**
** -------------------------- commentaire francais -----------------------------
** je parse mes argment sur le bon nombre doctet quils sont codé
** registre -> 01 - codé sur 1 octet
** direct -> 10 - codé sur 2 ou 4 octets (indiqué dans la global)
** indirect -> 11 - codé 2 octets
** jutilise le meme type de boucle que dans test_args
** while nb d'arg
********************************************************************************
*/

void	get_args(t_corevm *vm, t_process *process, t_op g_tab)
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
			get_one_octet(vm, process, i);
		else if (key == 2 && !g_tab.dir)
			get_four_octets(vm, process, i);
		else if (key == 3 || (key == 2 && g_tab.dir))
			get_two_octets(vm, process, i);
		dec -= 2;
		i++;
	}
}

/*
********************************************************************************
**	test_args checks if process->type_instruc[1] is the instruction accepted
**	by g_op_tab[process->type_instruc[0]]
**	process->type_instruc[0] = g_op_tab[i].id => opcode
**		0x10 pour aff
**	process->type_instruc[1] = key unique representant la nature des arguments
**		T_REG -> 1 -> 01 - codé sur 1 octet
**	 	T_DIR -> 2 -> 10 - codé sur 2 ou 10 4 octets
**	 	T_IND -> 4 -> 11 - codé 2 octets
**			(11 = 3 alors que 4 0100 ce qui revient 1 << (3-1))
**		exemple {T_REG , T_REG , T_REG} -> 54 -> 0101 0100
**		autre exemple {T_DIR, T_IND , T_REG} -> B4 ->
**		dans le tableau de global.c T_IND -> 4 (0100)
**		dans la process->type_instruc[1] c'est 3
**
** -------------------------- commentaire francais -----------------------------
** on va checker la key de nos arg pour voir
** si elle est toujours ok
** on fait une boucle avec le nb dagr de linstruction
** on decale binairement dabord de 6 pusi 4 puis 2
** et a chque tours
** on compare le resultat avec la global a la colone accept
** si le type de larg est accepté par linstruc ok sinn FALSE
********************************************************************************
*/

t_bool	test_args(t_process *process, t_op g_op_tab)
{
	char	key;
	int		i;
	int		dec;

	i = 0;
	dec = 6;
	while (i < 4)
	{
		key = (process->type_instruc[1] >> dec) & 3;
		if (i < g_op_tab.nbr_arg && key)
		{
			if (!(g_op_tab.accept[i] & (1 << (key - 1))))
				return (FALSE);
		}
		else if (key || i < g_op_tab.nbr_arg)
			return (FALSE);
		dec -= 2;
		i++;
	}
	return (TRUE);
}
