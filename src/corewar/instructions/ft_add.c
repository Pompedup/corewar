

#include "corewar.h"

/*
** 0x04
** additionne l'arg1 et l'arg2 et met le resultat dans l'arg3
** modifie le carry
*/

//Usage : add S(RG), S(RG), D(RG)
void	ft_add(t_corevm *vm, t_process *process)
{
	if (process->type_instruc[1] != 54)
		return ;
	get_one_octet(vm, process, 0);
	get_one_octet(vm, process, 1);
	get_one_octet(vm, process, 2);
	//execute l'instruction
}
