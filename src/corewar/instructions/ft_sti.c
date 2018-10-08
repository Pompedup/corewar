

#include "corewar.h"

/*
** 0x0b
** sti -> va copier le 1er param dans une adresse obtenu grace au 2 autres params
** sti r2,%4,%5 -
** sti copies REG_SIZE octets de r2 a laddresse (4 + 5)
** ici les params 2 et 3 sont des index
** si ce sont des registres, on utilisera leur contenu comme un index
*/

//Usage : sti S(RG), S(RG/ID/D2), S(RG/D2)
int		ft_sti(t_corevm *vm, t_process *process)
{
	int	*values;
	int i;

	i = 0;
	if (!(test_args(process, g_op_tab[process->type_instruc[0]])))
	{
		ft_printf(" ___________________STORE INDIRECT return 0\n");
		return (0);
	}
	get_args(vm, process, g_op_tab[process->type_instruc[0]]);

	values = get_values(vm, process, 7, 0); //6 car on veux recup la valeur de 2 derniers arg
	if (values)
	{
		ft_printf(" STORE INDIRECT values[0] d '%d' values[1] d '%d' values[2] d '%d'\n", values[0], values[1], values[2]);
		ft_printf(" STORE INDIRECT values[1] + values[2] int '%d'\n", values[1]+ values[2]);
		*(unsigned int *)(vm->core + ((process->pc + values[1] + values[2]) & (MEM_SIZE - 1))) = values[0];
		while (i < 4)
		{
			//revoir pour le CAST vm->color[(process->pc + (process->args[1] & (IDX_MOD - 1))) & (MEM_SIZE - 1)] = process->color;
			ft_printf("----------(process->pc + i + values[1] + values[2]) & (MEM_SIZE - 1) %d\n", (process->pc + i + values[1] + values[2]) & (MEM_SIZE - 1));
			vm->color[(process->pc + i + values[1] + values[2]) & (MEM_SIZE - 1)] = process->color + 4;
			i++;
		}
ft_printf(" STORE INDIRECT vm->core[(process->pc + values[1] + values[2]) & (MEM_SIZE - 1)] hexa '%x'\n", vm->core[(process->pc + values[1] + values[2])
			& (MEM_SIZE - 1)]);
		free(values);
	}
	return (1);
}
