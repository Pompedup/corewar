

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
	
	//if (vm->nbr_total_cycles > CYCLE_DEBUG)
	//ft_printf("\n LLLLLLLLLLLLLLLLLLLLLLIVE --%d--\n", process->num_player);

	get_four_octets(vm, process, 0);
	i = 0;
	while (process->args[0] != vm->lives_player[i][0]  && i < vm->info->nb_players)
		i++;
	if (process->args[0] == vm->lives_player[i][0])
	{
			//if (vm->nbr_total_cycles > CYCLE_DEBUG)
			//	ft_printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!liveee a allumer!!!!\n");
		vm->lives_player[i][1]++;
		//vm->lives_player[i][1] = process->pc & (MEM_SIZE - 1);
		process->color_live = process->pc & (MEM_SIZE - 1);
		//	if (vm->nbr_total_cycles > CYCLE_DEBUG)
			//	ft_printf("vm->lives_player[i][1] color_live %d\n", vm->lives_player[i][1]);
	}
	vm->nb_lives++; //est ce quil faut vraiment calculer le nb total de live?

	//	ft_printf("trouve bon processus number_to_be_alive %s,\n", number_to_be_alive);
	//	//ft_printf("un processus dit que le joueur %d(%s) est en vie\n", number_to_be_alive->reg[0], number_to_be_alive->name);
	//	ft_printf("process->pc & (MEM_SIZE - 1) %d\n", process->pc & (MEM_SIZE - 1));
	//ft_printf("core->vm process->pc & (MEM_SIZE - 1) %d\n", vm->core[process->pc & (MEM_SIZE - 1)]);

}

/*
void		ft_live(t_corevm *vm, t_process *process)
{
	t_process *number_to_be_alive;
	
	ft_printf("\n LLLLLLLLLLLLLLLLLLLLLLIVE  %d???\n", process->num_player);

	get_four_octets(vm, process, 0);
	//process->live++;
	number_to_be_alive = vm->info->first_processus;
	while (number_to_be_alive && process->args[0] != number_to_be_alive->num_player)
	{
		number_to_be_alive = number_to_be_alive->next;
	}
	ft_printf("trouve bon processus process->args[0] %d process->reg[0] %d,\n", process->args[0], process->num_player);
	//	ft_printf("trouve bon processus number_to_be_alive %s,\n", number_to_be_alive);
	if (number_to_be_alive)
	{
		ft_printf("number_to_be_alive->num_player %d,\n", number_to_be_alive->num_player);
		if (process->args[0] == number_to_be_alive->num_player)// && number_to_be_alive->reg[0] != process->reg[0])
			number_to_be_alive->live++;
	//	//ft_printf("un processus dit que le joueur %d(%s) est en vie\n", number_to_be_alive->reg[0], number_to_be_alive->name);
	//	ft_printf("process->pc & (MEM_SIZE - 1) %d\n", process->pc & (MEM_SIZE - 1));
		ft_printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!liveee a allumer!!!!\n");
		//ft_printf("core->vm process->pc & (MEM_SIZE - 1) %d\n", vm->core[process->pc & (MEM_SIZE - 1)]);
		number_to_be_alive->color_live = process->pc & (MEM_SIZE - 1);
		ft_printf("number_to_be_alive->color_live %d\n", number_to_be_alive->color_live);
		// vm->color[process->pc] = number_to_be_alive->color;
	}
	vm->nb_lives++; //est ce quil faut vraiment calculer le nb total de live?
}
*/