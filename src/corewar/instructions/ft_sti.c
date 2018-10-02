

#include "corewar.h"

/*
** 0x0b
** sti -> va copier le 1er param dans une adresse obtenu grace au 2 autres params
** sti r2,%4,%5 -
** sti copies REG_SIZE octets de r2 a laddresse (4 + 5)
** ici les params 2 et 3 sont des index
** si ce sont des registres, on utilisera leur contenu comme un index
*/

//Usage : sti S(RG), S(RG/ID/D2), S(ID/D2)
int		ft_sti(t_corevm *vm, t_process *process)
{
	int	*values;

	if (!(test_args(process, g_op_tab[process->type_instruc[0]])))
		return (0);
	get_args(vm, process, g_op_tab[process->type_instruc[0]]);

	values = get_values(vm, process, 7, 0); //6 car on veux recup la valeur de 2 derniers arg
printf(" STORE INDIRECT values[0] hexa '%x' values[1] hexa '%x' values[2] hexa '%x'\n", values[0], values[1], values[2]);
	if (values)
	{
		vm->core[(process->pc + values[1] + values[2]) & (MEM_SIZE - 1)] = values[0];
printf(" STORE INDIRECT vm->core[(process->pc + values[1] + values[2]) & (MEM_SIZE - 1)] hexa '%x'\n", vm->core[(process->pc + values[1] + values[2])
			& (MEM_SIZE - 1)]);
		free(values);
	}
	return (1);
}
