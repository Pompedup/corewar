

#include "corewar.h"

/*
** 0x03
** st -> store, met la valeur du 1er arg(un registre) dans le 2eme
** . Par exemple, st r1, 42 stocke la
valeur de r1 à l’adresse (PC + (42 % IDX_MOD))

** st r3,r8 copies r3 in r8
** ou st r3, r8 - copie r3 dans r8
*/

//Usage : st S(RG), D(RG/ID)
void	ft_st(t_corevm *vm, t_process *process)
{
	printf("ft_st\n");
	if (process->type_instruc[1] == 0x50) //{T_REG, T_REG}
	{
		get_one_octet(vm, process, 0);
		get_one_octet(vm, process, 1);
		//execute linstruction
	}
	if (process->type_instruc[1] == 0x70) //{T_REG, T_IND}
	{
		get_one_octet(vm, process, 0);
		get_two_octets(vm, process, 1);
		//execute linstruction
	}
}
