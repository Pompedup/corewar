

#include "corewar.h"

extern t_op	g_op_tab[];

/*
** 0x06
** ET bit à bit : l'arg1 & l'arg2 et met le resultat dans l'arg3
** and r2,%0,r3 - met r2 & 0 dans r3
** modifie le carry
*/

//Usage : and S(RG/ID/D4), S(RG/ID/D4), D(RG)
void	ft_and(t_corevm *vm, t_process *process)
{
	int	*values;

	if (g_op_tab[process->type_instruc[0]].nbr_arg > 1)
		if (!(test_args(process, g_op_tab[process->type_instruc[0]])))
			return ;
	get_args(vm, process, g_op_tab[process->type_instruc[0]]);

	values = get_values(vm, process, 3);
	printf("values[0] %d  values[1] %d\n", values[0], values[1]);
	if (values)
		process->reg[process->args[2]] = values[0] & values[1];

	printf("process->reg[process->args[2]] %d\n", process->reg[process->args[2]]);
	free(values);
}
