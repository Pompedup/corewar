

#include "corewar.h"

/*
** 0x0f
** lfork -> long fork, meme chose que fork sans le % IDX_MOD
** lFork %34 crée un nouveau programme a (PC + 34)
** modifie le carry
** voir si comme on a pas le IDX_MOD on a pas dautre limitation quand meme genre
** % MEM_SIZE pour rester dans la memoire circulaire de notre core!!!
*/

//Usage : lfork S(D2)
int		ft_lfork(t_corevm *vm, t_process *process)
{
	(void)vm;

	//il y a un seul arg donc pas de key arg a checker!!

	process->pc += 3;
	//on avance le pc pour la mettre au niveau de la prochaine instruction
	//pourquoi +2 : 1 octet pour linstrution 1 (comme il y a quun arg pour cette fonction on a pas de key argument)
	//et + 1 pour l'argument de type direct codé sur deux octets
	return (1);
}
