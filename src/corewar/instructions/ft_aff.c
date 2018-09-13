

#include "corewar.h"

/*
** 0x10
** aff -> Elle prend en paramètre un registre
** et affiche le caractère dont le code ascii est présent dans ce registre
** (un modulo 256 est applique au code ascii,
** le caractère est affiché sur la sortie standard)
** Ex: ld %52,r3
** aff r3
** affiche '*' sur la sortie standard
*/

//Usage : aff S(RG)
void	ft_aff(t_corevm *vm, t_process *process)
{
	(void)vm;

	process->pc += 2;
	//on avance le pc pour la mettre au niveau de la prochaine instruction
	//pourquoi +2 : 1 octet pour linstrution 1 (comme il y a quun arg pour cette fonction on a pas de key argument)
	//et + 1 pour l'argument de type registre
}
