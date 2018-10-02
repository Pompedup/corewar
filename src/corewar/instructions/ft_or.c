

#include "corewar.h"

/*
** 0x07
** ou inclusif
** OR bit à bit : l'arg1 | l'arg2 et met le resultat dans l'arg3
** modifie le carry
*/

//Usage : or S(RG/ID/D4), S(RG/ID/D4), D(RG)
int		ft_or(t_corevm *vm, t_process *process)
{
	(void)vm;
	(void)process;/*
	int	*args;

	args = get_args_and_or_xor(vm, process);
	if (args)
	{
		get_one_octet(vm, process, 2);
		process->reg[process->args[2]] = args[0] || args[1];
	}*/
		return (1);
}
