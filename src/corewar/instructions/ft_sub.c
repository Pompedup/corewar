

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

	if (process->type_instruc[1] != 0x54)
		return ;
	ft_printf("	process->type_instruc[1] %x \nsub\n", process->type_instruc[1]);
	get_args(vm, process, g_op_tab[process->type_instruc[0]]);
	values = get_values(vm, process, 3);
	printf(" SUB values[0] %d  values[1] %d\n", values[0], values[1]);
	if (values)
	{
		process->reg[process->args[2]] = values[0] - values[1];
		vm->info->first_processus->carry = (process->reg[process->args[2] - 1]) ? 0 : 1;//comme ca pour modifier le carry?
		free(values);
	}
}
