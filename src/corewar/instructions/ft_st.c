

#include "corewar.h"

/*
** 0x03
** st -> store, met la valeur du 1er arg(un registre) dans le 2eme
** st 34, r3 - charge les REG_SIZE octets a partir de ladresse
** ( PC + (34 % IDX_MOD))
** ou st r3, r8 - copie r3 dans r8
*/

//Usage : st S(RG), D(RG/ID)
void	ft_st(t_corevm *vm, t_process *process)
{
	(void)vm;
	if (process->type_instruc[1] == REG_CODE
		&& process->type_instruc[2] == IND_CODE
			&& process->type_instruc[3] == 0
				&& && process->type_instruc[4] == 0)
	{
		//executer lintruction
		process->pc += 5 //si deuxieme arg est un indirect
	}


	ou
	else if (process->type_instruc[1] == REG_CODE
		&& process->type_instruc[2] == REG_CODE
			&& process->type_instruc[3] == 0
				&& process->type_instruc[4] == 0)
	{
		//executer lintruction
		process->pc += 4 //si deuxieme arg est un registre
	}

}
