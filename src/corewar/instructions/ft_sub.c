

#include "corewar.h"

/*
** 0x05
** soustraction : l'arg1 - l'arg2 et met le resultat dans l'arg3
** modifie le carry
*/

//Usage : sub S(RG), S(RG), D(RG)
int		ft_sub(t_corevm *vm, t_process *process)
{
	int	*values;

	if (process->type_instruc[1] != 0x54)
		return (0);
	ft_printf("	process->type_instruc[1] %x \nsub\n", process->type_instruc[1]);
	get_args(vm, process, g_op_tab[process->type_instruc[0]]);
	values = get_values(vm, process, 3, 0);
	ft_printf(" SUB values[0] %d  values[1] %d\n", values[0], values[1]);
	if (values)
	{
		process->reg[process->args[2]] = values[0] - values[1];
		process->carry = (process->reg[process->args[2]]) ? 0 : 1;//comme ca pour modifier le carry?
		free(values);
	}
	return (1);
}
