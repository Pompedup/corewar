/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arguments.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 15:16:23 by ccoupez           #+#    #+#             */
/*   Updated: 2018/09/19 17:59:55 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"


/*
** Applique un & (ET bit-à-bit) sur les deux premiers paramètres, et stocke le
résultat dans le registre qui est le 3ème paramètre. Opcode 0x06. Modifie le carry.

** recupere les arguments pour les fonctions and or et xor
** ca fait un peu foret de fi dsll donc peut etre a opti
** teste toute les possibilites de type pour chaque args
** et ca avamce le pc dans les fonctions get_octets ci dessus !!
*/

int		*get_args_and_or_xor_ldi(t_corevm *vm, t_process *process)
{
	int	*values;

	if (!(values = malloc(sizeof(int) * 3)))
		return (NULL);
	if (((process->type_instruc[1] >> 6) & 3) == 1)
		values[0] = process->reg[process->args[0]];
	else if (((process->type_instruc[1] >> 6) & 3) == 2)
		values[0] = process->args[0];
	else if (((process->type_instruc[1] >> 6) & 3) == 3)
		values[0] = vm->core[(process->pc + (process->args[1] % IDX_MOD)) % MEM_SIZE];



	if (((process->type_instruc[1] >> 4) & 3) == 1)
		values[1] = process->reg[process->args[1]];
	else if (((process->type_instruc[1] >> 4) & 3) == 2)
		values[1] = process->args[1];
	else if (((process->type_instruc[1] >> 4) & 3) == 3)
		values[1] = vm->core[(process->pc + (process->args[1] % IDX_MOD)) % MEM_SIZE];


	return (values);
}



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
** je recupere mes argment sur le bon nombre doctet quils sont codé
** registre -> 01 - codé sur 1 octet
** direct -> 10 - codé sur 2 ou 4 octets (indiqué dans la global)
** indirect -> 11 - codé 2 octets
** jutilise le meme type de boucle que dans test_args
** while nb d'arg
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
** on va checker la key de nos arg pour voir
** si elle est toujours ok
** on fait une boucle avec le nb dagr de linstruction
** on decale binairement dabord de 6 pusi 4 puis 2
** et a chque tours
** on compare le resultat avec la global a la colone accept
** si le type de larg est accepté par linstruc ok sinn FALSE
*/

t_bool	test_args(t_process *process, t_op g_tab)
{
	char	key;
	int		i;
	int		dec;

	i = 0;
	dec = 6;

	while (i < 4)
	{
		key = (process->type_instruc[1] >> dec) & 3;
		if (i < g_tab.nbr_arg && key)
		{
			if (!(g_tab.accept[i] & (1 << (key - 1))))
				return (FALSE);
		}
		else if (key || i < g_tab.nbr_arg)
			return (FALSE);
		dec -= 2;
		i++;
	}
	printf("TRUE test args\n");
	return (TRUE);
}
