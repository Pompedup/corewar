/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arguments.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecesari <ecesari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 15:16:23 by ccoupez           #+#    #+#             */
/*   Updated: 2018/10/01 14:29:49 by ecesari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"


/*
** avec get_args on a parse le joueur et recupéré les arguments de la fonction
** ensuite ici on recupère la valeur de ces arguments
** (on les recupère de manière différentes selon qu'ils soient des registre direct ou indirect)
** cette fonction est génériaue à les toutes les fonctions
** on boucle 3 fois car 3 nb ax d'argument
** le num_arg quon envoie nous permet de connaitre les args quon veut recuperer
** 001 on recup que le 1er arg 011 les 2 premier 101 le permier et le 3eme...
** et ensuite en fonction de la key de linstruction on recup larg selon son type

*/

int		*get_values(t_corevm *vm, t_process *process, char num_arg)
{
	int	*values;
	int	dec;
	int	i;

	if (!(values = malloc(sizeof(int) * 3)))
		return (NULL);
	dec = 6;
	i = 0;
	while (i < 3)
	{
		if (num_arg & (1 << i))
		{
			if (((process->type_instruc[1] >> dec) & 3) == 1)
				values[i] = process->reg[process->args[i] - 1];
			else if (((process->type_instruc[1] >> dec) & 3) == 2)
				values[i] = process->args[i];
			else if (((process->type_instruc[1] >> dec) & 3) == 3)
				values[i] = vm->core[(process->pc
					+ (process->args[i] % IDX_MOD)) & (MEM_SIZE - 1)];
		}
		dec -= 2;
		i++;
	}
	return (values);
}

/*
** recupère seulement les registres (codé sur 1 octet)
*/

void	get_one_octet(t_corevm *vm, t_process *process, int i)
{
	process->args[i] = *(vm->core + (process->pc & (MEM_SIZE - 1)));
	process->pc += 1;
	printf("arg 1 octet %x\n", process->args[i]);
	// ft_printf("vm->core[process->pc] %x\n", vm->core[process->pc]);
}

/*
** recupère les indirects et une partie des directs codé sur 2 octets
*/

void	get_two_octets(t_corevm *vm, t_process *process, int i)
{
	process->args[i] =
		*((unsigned short*)(vm->core + (process->pc & (MEM_SIZE - 1))));
	ft_memrev((char*)&process->args[i], 2);
	process->pc += 2;
	// ft_printf("vm->core[process->pc] %x\n", vm->core[process->pc]);
	printf("arg 2 octets %x\n", process->args[i]);
}

/*
** recupère une partie des directs codé sur 4 octets)
*/

void	get_four_octets(t_corevm *vm, t_process *process, int i)
{
	process->args[i] = *((unsigned int*)(vm->core + (process->pc & (MEM_SIZE - 1))));
	ft_memrev((char*)&process->args[i], 4);
	process->pc += 4;
	// ft_printf("vm->core[process->pc] %x\n", vm->core[process->pc]);
	printf("arg 4 octets %x\n", process->args[i]);
}

/*
********************************************************************************
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
		// printf("get arg\n");
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
	printf("TRUE test args\n");
	return (TRUE);
}
