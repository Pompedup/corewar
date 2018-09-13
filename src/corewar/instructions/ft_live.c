

#include "corewar.h"

/*
** live-> dit que je suis en vie
sont instruction c'est :
** 0x01 suivie de 4 octets qui represente le numero du joueur
*/

//Usage : live S(D4)
void	ft_live(t_corevm *vm, t_process *process)
{
	(void)process;
	//if (vm->core[process->pc + 1 % MEM_SIZE] == process->reg[0]) ou alors un direct indique
															//un adress donc ca va pas mon if
		//process->alive = 1;
	vm->nb_lives++;
	printf("un processus dit que le joueur %d(%s) est en vie",
		process->reg[0], process->name);


	process->pc += 2;
	//on avance le pc pour la mettre au niveau de la prochaine instruction
	//pourquoi +2 : 1 octet pour linstrution 1 (comme il y a quun arg pour cette fonction on a pas de key argument)
	//et + 1 pour l'argument de type registre
}
