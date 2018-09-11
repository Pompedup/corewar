

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

//void	aff(char *reg)
void	ft_aff(t_corevm *vm, t_process *process)
{
	(void)vm;
	(void)process;
}
