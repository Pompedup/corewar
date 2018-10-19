/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_values.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecesari <ecesari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 11:42:33 by ccoupez           #+#    #+#             */
/*   Updated: 2018/10/19 20:25:33 by ecesari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		get_ind_value(t_corevm *vm, t_process *p, int i, int l)
{
	int	add;
	int	v;
	int	j;

	add = p->args[i];
	if (!l)
		add = (p->args[i] % IDX_MOD) - IDX_MOD
			* (((p->args[i] - 1) / IDX_MOD) & 1);
	if (((add + p->pc) & (MEM_SIZE - 1)) >= MEM_SIZE - 4)
	{
		j = -1;
		while (j++ < 4)
			((char *)(&v))[j] = *(vm->core + ((p->pc + add + j)
				& (MEM_SIZE - 1)));
	}
	else
	{
		if (l)
			v = *((int*)(vm->core + ((p->pc + (p->args[i] & (MEM_SIZE - 1)))
				& (MEM_SIZE - 1))));
		else
			v = *((int*)(vm->core + ((p->pc + add) & (MEM_SIZE - 1))));
	}
	ft_memrev(&v, 4);
	return (v);
}

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
		ft_error(vm, FAIL_MEMALLOC_4, 0);
	dec = 6;
	i = -1;
	while (++i < 3)
	{
		if (num_arg & (1 << i))
		{
			if (((process->type_instruc[1] >> dec) & 3) == 1)
				values[i] = process->reg[process->args[i]];
			else if (((process->type_instruc[1] >> dec) & 3) == 2)
				values[i] = process->args[i];
			else if (((process->type_instruc[1] >> dec) & 3) == 3)
				values[i] = get_ind_value(vm, process, i, l);
		}
		dec -= 2;
	}
	return (values);
}
