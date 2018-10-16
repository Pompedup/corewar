

#include "corewar.h"

/*
********************************************************************************
** 0x0c
** fork -> cree un nouveau programme qui est execute a ladresse :
** (PC + (first parameter % IDX_MOD)
** Fork %34 crée un nouveau programme a (PC + (34 % IDX_MOD)
** Le nouveau programme herite des differents etats du pere
** cad on copie colle toutes les instruction du champion a un autre androit
** dans la memoire!!
** sachan quon a enregistrer nos programmes dans une liste / chaine
**	(peut etre a voir ca)
** si on cree un nouveau programme on cree un nouveau maillon de notre liste
** au tout debut on a nb_programme == nb_champion
** le nombre de programme  en execution augmente lorsquon fait un fork
** (ou lfork je pense aussi)
********************************************************************************
*/

//Usage : fork S(D2)
void	ft_fork(t_corevm *vm, t_process *process)
{
	int			i;
	t_player	*tmp_player;
	t_process	*fork;

	tmp_player = vm->info->first_player;
	fork = NULL;
	get_two_octets(vm, process, 0);
	//ft_printf(" process->args[0]  %x\n", (process->args[0] ));
	//ft_printf(" (process->args[0] & (IDX_MOD - 1) %d\n", (process->args[0] & (IDX_MOD - 1)));
	while (ft_strcmp(process->name, tmp_player->header->prog_name) && tmp_player)
	{
		tmp_player = tmp_player->next;
	}
	if (tmp_player)
	{
		//int add = ((short)process->args[0] % IDX_MOD) - IDX_MOD * (((process->args[0]) / IDX_MOD) & 1);
		//ft_printf("%d short\n", (short)process->args[0]);
		//ft_printf("%d \n", process->args[0]);
		//ft_printf("pc %d\n", add);
		//fork = create_process(vm, ((process->pc + add) & (MEM_SIZE - 1)), tmp_player);
		 fork = create_process(vm, ((process->pc + ((short)process->args[0] % IDX_MOD)) & (MEM_SIZE - 1)), tmp_player);

		//ft_printf("FORKKKKKKKKK fork->pc %d\n)",  fork->pc);
	}
	i = 0;
	while (i < REG_NUMBER)
	{
		fork->reg[i] = process->reg[i];
		i++;
	}
	put_process_front(&vm->info->first_processus, fork);
}
