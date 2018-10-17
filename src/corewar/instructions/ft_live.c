

#include "corewar.h"

/*
** live-> dit que je suis en vie
sont instruction c'est :
** 0x01 suivie de 4 octets qui represente le numero du joueur
*/

//Usage : live S(D4)
void		ft_live(t_corevm *vm, t_process *process)
{
	int			i;

	// if (vm->nbr_total_cycles > CYCLE_DEBUG)
	// ft_printf("\n LLLLLLLLLLLLLLLLLLLLLLIVE --%d--\n", process->num_player);
	get_four_octets(vm, process, 0);
	i = 0;
	while (process->num_player != vm->lives_player[i][0])
		i++;
	vm->lives_player[i][3] = 1;
	while (process->args[0] != vm->lives_player[i][0]  && i < vm->info->nb_players)
		i++;
	if (process->args[0] == vm->lives_player[i][0])
	{
			// if (vm->nbr_total_cycles > CYCLE_DEBUG)
				// ft_printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!liveee a allumer!!!!\n");
		vm->lives_player[i][1]++;
		vm->lives_player[i][2] = vm->nbr_total_cycles;
		//vm->lives_player[i][1] = process->pc & (MEM_SIZE - 1);
		process->color_live = process->pc & (MEM_SIZE - 1);
			// if (vm->nbr_total_cycles > CYCLE_DEBUG)
				// ft_printf("vm->lives_player[i][1] color_live %d\n", vm->lives_player[i][1]);
	}
	vm->nb_lives++; //est ce quil faut vraiment calculer le nb total de live?

	//	ft_printf("trouve bon processus number_to_be_alive %s,\n", number_to_be_alive);
	//	//ft_printf("un processus dit que le joueur %d(%s) est en vie\n", number_to_be_alive->reg[0], number_to_be_alive->name);
	//	ft_printf("process->pc & (MEM_SIZE - 1) %d\n", process->pc & (MEM_SIZE - 1));
	//ft_printf("core->vm process->pc & (MEM_SIZE - 1) %d\n", vm->core[process->pc & (MEM_SIZE - 1)]);

}
