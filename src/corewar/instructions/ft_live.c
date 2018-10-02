

#include "corewar.h"

/*
** live-> dit que je suis en vie
sont instruction c'est :
** 0x01 suivie de 4 octets qui represente le numero du joueur
*/

//Usage : live S(D4)
int		ft_live(t_corevm *vm, t_process *process)
{
	t_process *tmp;


	//a voir sil y a des mooment ou on renvoie 0
	//et revoir toute la fonction sur comment on compte les live
	get_four_octets(vm, process, 0);
	tmp = vm->info->first_processus;
	while (tmp && process->args[0] != tmp->reg[0])
	{
		tmp = tmp->next;
	}
	if (process->args[0] == tmp->reg[0])
		tmp->live++;
	vm->nb_lives++; //est ce quil faut vraiment calculer le nb total de live?
	printf("un processus dit que le joueur %d(%s) est en vie", process->reg[0], tmp->name);
	return (1);
}
