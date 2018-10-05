

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
int		ft_zjmp(t_corevm *vm, t_process *process)
{
	if (!process->carry)
	{
		ft_printf("no carry no zjmp\n");
		return (0);
	}
	if (vm->color[process->pc] < 12 && vm->color[process->pc] > 7)
		vm->color[process->pc] -= 8;
	else if (vm->color[process->pc] == 12)
		vm->color[process->pc]++;
	get_two_octets(vm, process, 0);
	printf(" AVANT ZJUMP process->pc int '%d' \n", process->pc);
	process->pc += (process->args[0] & (IDX_MOD - 1));
	printf(" APRES ZJUMP process->pc int '%d' \n", process->pc);
	process->pc_tmp = 0;
	// if (vm->color[process->pc] < 8)
		// vm->color[process->pc] = vm->color[process->pc] < 4 ? vm->color[process->pc] + 8 : vm->color[process->pc] + 4;//pour les cas de fork
	// if (vm->color[process->pc] == 13)
		// vm->color[process->pc]--;// = process->color + 8;
	return (1);
}
