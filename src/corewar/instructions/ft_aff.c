

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
	char	c;

	get_one_octet(vm, process, 0);
	c = process->reg[process->args[0] % 256];
	ft_printf("AFF");
	write(1, &c, 1);
	ft_printf("\n");
}
