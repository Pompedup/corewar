

#include "corewar.h"

/*
** live-> dit que je suis en vie
sont instruction c'est :
** 0x01 suivie de 4 octets qui represente le numero du joueur
*/

//Usage : live S(D4)
int		ft_live(t_corevm *vm, t_process *process)
{
	t_process *number_to_be_alive;

ft_printf("\nLIVE ???\n");
	//a voir sil y a des mooment ou on renvoie 0
	//surement quand le joueur est mort
	get_four_octets(vm, process, 0);
	number_to_be_alive = vm->info->first_processus;
	while (number_to_be_alive && process->args[0] != number_to_be_alive->reg[0])
	{
		number_to_be_alive = number_to_be_alive->next;
	}
	if (process->args[0] == number_to_be_alive->reg[0])
		number_to_be_alive->live++;
	vm->nb_lives++; //est ce quil faut vraiment calculer le nb total de live?
	printf("un processus dit que le joueur %d(%s) est en vie\n", number_to_be_alive->reg[0], number_to_be_alive->name);
	return (1);
}
