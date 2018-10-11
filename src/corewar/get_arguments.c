/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arguments.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 15:16:23 by ccoupez           #+#    #+#             */
/*   Updated: 2018/10/11 17:07:44 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
********************************************************************************
**	get_values
** -------------------------- commentaire francais -----------------------------
** avec get_args on a parse la core et recupéré les arguments de la fonction
** ensuite ici on recupère la valeur de ces arguments
** cette fonction est génériale à les toutes les fonctions
** on boucle 3 fois car il y a 3 arguments max
** le num_arg quon envoie nous permet de connaitre les args quon veut recuperer
** 001 on recup que le 1er arg 011 les 2 premier 101 le permier et le 3eme...
** en fonction de la key de l'instruction on recup larg selon son type
********************************************************************************
*/

int		*get_values(t_corevm *vm, t_process *process, char num_arg, int l)
{
	int	*values;
	int	dec;
	int	i;

	if (!(values = ft_memalloc(sizeof(int) * 3)))
		return (NULL); //quand on aura mis bien le retour enlever le if (values) dans toutes les intructions
		// ft_error(vm, FAIL_MEMALLOC_5, 0);
	dec = 6;
	i = -1;
	while (++i < 3)
	{
		if (num_arg & (1 << i))
		{
			if (((process->type_instruc[1] >> dec) & 3) == 1)
			{
				values[i] = process->reg[process->args[i]];
				//ft_memrev(&values[i], 4);
			}
			else if (((process->type_instruc[1] >> dec) & 3) == 2)
				values[i] = process->args[i];
			else if (((process->type_instruc[1] >> dec) & 3) == 3)
			{
				//ft_printf("indirrrrrr__________________________________________________________\n");
				values[i] = *((unsigned int*)(vm->core + ((process->pc + (process->args[i] & (l ? MEM_SIZE - 1 : IDX_MOD - 1)))
						& (MEM_SIZE - 1))));
				ft_memrev(&values[i], 4);

			}
		}
		dec -= 2;
	}
	return (values);
}

/*
********************************************************************************
**
** -------------------------- commentaire francais -----------------------------
** recupère seulement les registres codés sur 1 octet
********************************************************************************
*/

void	get_one_octet(t_corevm *vm, t_process *process, int i)
{
	process->args[i] =
		*(vm->core + ((process->pc + process->pc_tmp) & (MEM_SIZE - 1))) - 1;
	process->pc_tmp += 1;
	//if (vm->nbr_total_cycles > CYCLE_DEBUG)
	//	ft_printf("arg 1 octet %x\n", process->args[i]);
	// ft_printf("vm->core[process->pc] %x\n", vm->core[process->pc]);
}

/*
********************************************************************************
** -------------------------- commentaire francais -----------------------------
** recupère les indirects et une partie des directs codés sur 2 octets
********************************************************************************
*/

void	get_two_octets(t_corevm *vm, t_process *process, int i)
{
	process->args[i] =
		*((unsigned short*)(vm->core + ((process->pc + process->pc_tmp) & (MEM_SIZE - 1))));
	ft_memrev((char*)&process->args[i], 2);
	process->pc_tmp += 2;
	// ft_printf("vm->core[process->pc] %x\n", vm->core[process->pc]);
	//if (vm->nbr_total_cycles > CYCLE_DEBUG)
	//	ft_printf("arg 2 octets %x\n", process->args[i]);
}

/*
********************************************************************************
** -------------------------- commentaire francais -----------------------------
** recupère une partie des directs codés sur 4 octets)
********************************************************************************
*/

void	get_four_octets(t_corevm *vm, t_process *process, int i)
{
	process->args[i] =
		*((unsigned int*)(vm->core + ((process->pc + process->pc_tmp) & (MEM_SIZE - 1))));
	ft_memrev((char*)&process->args[i], 4);
	process->pc_tmp += 4;
	// ft_printf("vm->core[process->pc] %x\n", vm->core[process->pc]);
	//if (vm->nbr_total_cycles > CYCLE_DEBUG)
	//	ft_printf("arg 4 octets %x\n", process->args[i]);
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
		//if (vm->nbr_total_cycles > CYCLE_DEBUG)
		//	ft_printf("get arg process->type_instruc[0] hexa %x\n", process->type_instruc[0]);
		key = (process->type_instruc[1] >> dec) & 3;
		if (key == 1) //un registre
			get_one_octet(vm, process, i);
		else if (key == 2 && !g_tab.dir) //un direct sur 4
			get_four_octets(vm, process, i);
		else if (key == 3 || (key == 2 && g_tab.dir)) //un indirect ou un direct sur 2
			get_two_octets(vm, process, i);
		dec -= 2;
		i++;
	}
}

/*
********************************************************************************
**	test_args checks if process->type_instruc[1] is the instruction accepted by g_op_tab[process->type_instruc[0]]
**	process->type_instruc[0] = g_op_tab[i].id => opcode
**		0x10 pour aff
**	process->type_instruc[1] = key unique representant la nature des arguments
**		T_REG -> 1 -> 01 - codé sur 1 octet
**	 	T_DIR -> 2 -> 10 - codé sur 2 ou 10 4 octets
**	 	T_IND -> 4 -> 11 - codé 2 octets (11 = 3 alors que 4 0100 ce qui revient 1 << (3-1))
**		exemple {T_REG , T_REG , T_REG} -> 54 -> 0101 0100
**		autre exemple {T_DIR, T_IND , T_REG} -> B4 ->
**		dans le tableau de global.c T_IND -> 4 (0100) dans la process->type_instruc[1] c'est 3
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
	//ft_printf("dans test_args process->type_instruc[1]> hexa %x\n", process->type_instruc[1]>> dec);
		key = (process->type_instruc[1] >> dec) & 3;
		if (i < g_op_tab.nbr_arg && key)
		{
			if (!(g_op_tab.accept[i] & (1 << (key - 1))))
			{
				//ft_printf("sortie 1 g_op_tab.accept[%d] %d g_op_tab.shortcut %s\n\n", i, g_op_tab.accept[i], g_op_tab.shortcut);
				return (FALSE);
			}
		}
		else if (key || i < g_op_tab.nbr_arg)
		{
			//ft_printf("sortie 2\n\n");
			return (FALSE);
		}
		dec -= 2;
		i++;
	}
	//printf("TRUE test args\n");
	return (TRUE);
}
