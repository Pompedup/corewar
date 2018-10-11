

#include "corewar.h"

/*
** live-> dit que je suis en vie
sont instruction c'est :
** 0x01 suivie de 4 octets qui represente le numero du joueur
*/

//Usage : live S(D4)
void		ft_live(t_corevm *vm, t_process *process)
{
	t_process *number_to_be_alive;

//ft_printf("\nLIVE ???\n");

	get_four_octets(vm, process, 0);
	process->live++;
	number_to_be_alive = vm->info->first_processus;
	while (number_to_be_alive && process->args[0] != number_to_be_alive->reg[0])
	{
		number_to_be_alive = number_to_be_alive->next;
	}
	//ft_printf("trouve bon processus process->args[0] %x process->reg[0] %x,\n", process->args[0], process->reg[0]);
	//	ft_printf("trouve bon processus number_to_be_alive %s,\n", number_to_be_alive);
	if (number_to_be_alive)
	{
		if (process->args[0] == number_to_be_alive->reg[0] && number_to_be_alive->reg[0] != process->reg[0])
			number_to_be_alive->live++;
	//	ft_printf("un processus dit que le joueur %d(%s) est en vie\n", number_to_be_alive->reg[0], number_to_be_alive->name);
	//	ft_printf("process->pc & (MEM_SIZE - 1) %d\n", process->pc & (MEM_SIZE - 1));
		//ft_printf("core->vm process->pc & (MEM_SIZE - 1) %d\n", vm->core[process->pc & (MEM_SIZE - 1)]);

		number_to_be_alive->color_live = process->pc & (MEM_SIZE - 1);
		// vm->color[process->pc] = number_to_be_alive->color;
	}
	vm->nb_lives++; //est ce quil faut vraiment calculer le nb total de live?
}
