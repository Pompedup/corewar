

#include "corewar.h"

/*
** 0x09
** jump -> fait un saut à l'adresse passée en parametre
** SI le carry est a 1
** si le carry nest pas a 1 il ne fait rien mais consomme le meme temps
** zjmp %23 -
** si carry == 1 -
** met (PC + (23 % IDX_MOD)) DANS le PC
** on fait faire un saut a notre pointeur sur processus
** pour quil aille a un autre endroit de notre p    rogramme et continue de lire
** les instruction depuis cette nouvelle adresse
*/

//Usage : zjmp S(D2)
void	ft_zjmp(t_corevm *vm, t_process *process)
{
	(void)vm;

		//il y a un seul arg donc pas de key arg a checker!!

	process->pc += 3;
	//on avance le pc pour la mettre au niveau de la prochaine instruction
	//pourquoi +2 : 1 octet pour linstrution 1 (comme il y a quun arg pour cette fonction on a pas de key argument)
	//et + 1 pour l'argument de type direct codé sur deux octets
}
