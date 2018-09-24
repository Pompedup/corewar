

#include "corewar.h"

/*
** 0x0c
** fork -> cree un nouveau programme qui est execute a ladresse :
** (PC + (first parameter % IDX_MOD)
** Fork %34 crée un nouveau programme a (PC + (34 % IDX_MOD)
** Le nouveau programme herite des differents etats du pere
** cad on copie colle toutes les instruction du champion a un autre androit
** dans la memoire!!
** sachan quon a enregistrer nos programmes dans une liste / chaine (peut etre a voir ca)
** si on cree un nouveau programme on cree un nouveau maillon de notre liste
** au tout debut on a nb_programme == nb_champion
** le nombre de programme  en execution augmente lorsquon fait un fork
** (ou lfork je pense aussi)
*/

//Usage : fork S(D2)
void	ft_fork(t_corevm *vm, t_process *process)
{
	get_two_octets(vm, process, 0);
	// vm->core[(process->pc + (process->args[0] % IDX_MOD)) % MEM_SIZE] =
	//un nouveau programme herite des differents etats du pere;

}
