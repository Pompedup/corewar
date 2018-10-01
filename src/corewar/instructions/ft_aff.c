

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

	if (vm->core[process->pc & (MEM_SIZE - 1)] != 0x40)
		return ;
	process->pc++;
	get_one_octet(vm, process, 0);
	ft_printf("\tprocess->args[0] hexa '%x'\n", process->args[0]);
	ft_printf("\tprocess->reg[process->args[0] - 1] hexa '%x'\n", process->reg[process->args[0] - 1]);
	c = process->reg[process->args[0]] % 256;
	ft_printf("AFF c '%c'\t", c);
	write(1, &c, 1);
	ft_printf("\n");
}
