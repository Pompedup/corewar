

#include "corewar.h"

/*
** 0x05
** soustraction : l'arg1 - l'arg2 et met le resultat dans l'arg3
** modifie le carry
*/

//Usage : sub S(RG), S(RG), D(RG)
void	ft_sub(t_corevm *vm, t_process *process)
{
	int	*values;

	if (process->type_instruc[1] != 54)
		return ;
	get_args(vm, process, g_op_tab[process->type_instruc[0]]);
	values = get_values(vm, process, 3);

	if (values)
		process->reg[process->args[2]] = values[0] - values[1];

	//MODIFIE LE CARRY ????!!!!!

	free(values);
}
