

#include "corewar.h"

/*
** live-> dit que je suis en vie
sont instruction c'est :
** 0x01 suivie de 4 octets qui represente le numero du joueur
*/

//void	live(char *dir)
void	ft_live(t_corevm *vm, t_process *process)
{
	(void)process;
	vm->nb_live++;
}
