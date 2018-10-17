

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
	get_two_octets(vm, process, 0);
//	ft_printf("ZZZZZZJJJUUUMMMPPPP\n");
//	ft_printf("process->carry %d\n", process->carry);
	if (!process->carry)
	{
	//	ft_printf("process->carry %d\n", process->carry);
	//	ft_printf("no carry no zjmp\n");
		return ;
	}
	if (vm->color[process->pc & (MEM_SIZE - 1)] < 12 && vm->color[process->pc & (MEM_SIZE - 1)] > 7)
		vm->color[process->pc & (MEM_SIZE - 1)] -= 8;
	else if (vm->color[process->pc & (MEM_SIZE - 1)] == 12)
		vm->color[process->pc & (MEM_SIZE - 1)]++;
	//	ft_printf(" AVANT ZJUMP process->pc int '%d' \n", process->pc);
	//ft_printf(" AVANT ZJUMP ((short)(process->args[0])) sort x '%x' \n", ((short)(process->args[0])));
	//ft_printf(" AVANT ZJUMP p((process->args[0])) d '%d' \n", ((process->args[0])));

//a re assimiller!!!!!!!!!!!!!!!!!!!!!!!!!


	// int add = ((short)process->args[0] % IDX_MOD) - IDX_MOD * (((process->args[0]) / IDX_MOD) & 1);
	// process->pc += add;
	process->pc += (((short)process->args[0]) % IDX_MOD);

//	ft_printf(" + (((short)process->args[0]) & (IDX_MOD - 1) '%d' \n", (((short)process->args[0]) & (IDX_MOD - 1)));

	process->pc = process->pc & (MEM_SIZE - 1);
	//ft_printf(" APRES ZJUMP process->pc int '%d' \n", process->pc);
	process->pc_tmp = 0;

}
