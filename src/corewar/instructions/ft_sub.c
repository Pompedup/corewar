

#include "corewar.h"

/*
** 0x05
** soustraction : l'arg1 - l'arg2 et met le resultat dans l'arg3
** modifie le carry
*/

//Usage : sub S(RG), S(RG), D(RG)
void	ft_sub(t_corevm *vm, t_process *process)
{
	(void)vm;

		if (process->type_instruc[1] != REG_CODE
			&& process->type_instruc[2] != REG_CODE
				&& process->type_instruc[3] != REG_CODE
					&& process->type_instruc[4] != 0)
			ft_error(vm, 88);

		process->pc += 5;
		//on avance le pc pour la mettre au niveau de la prochaine instruction
		//pourquoi +5 : 1 octet pour linstrution 1 pour la key des arguguments
		//et +3 pour les 3 arguments de type registre
}
