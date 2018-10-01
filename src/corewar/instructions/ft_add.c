

#include "corewar.h"

/*
** 0x04
** additionne l'arg1 et l'arg2 et met le resultat dans l'arg3
** modifie le carry
*/

//Usage : add S(RG), S(RG), D(RG)
void	ft_add(t_corevm *vm, t_process *process)
{
	int	*values;

	if (process->type_instruc[1] != 0x54)
		return ;
	get_args(vm, process, g_op_tab[process->type_instruc[0]]);
	values = get_values(vm, process, 3);
	if (values)
	{
		process->reg[process->args[2]] = values[0] + values[1];
printf(" ADD values[0] %d  values[1] %d process->reg[process->args[2]] %d\n", values[0], values[1], process->reg[process->args[2]]);
		vm->info->first_processus->carry = (process->reg[process->args[2] - 1]) ? 0 : 1;
		free(values);
	}
}
