

#include "corewar.h"

/*
** 0x0c
** fork -> cree un nouveau programme qui est execute a ladresse :
** (PC + (first parameter % IDX_MOD)
** Fork %34 crée un nouveau programme a (PC + (34 % IDX_MOD)
** Le nouveau programme herite des differents etats du pere
** cad on copie colle toutes les instruction du champion a un autre androit
** dans la memoire!!
** sachan quon a enregistrer nos programmes dans une liste chaine (peut etre a voir ca)
** si on cree un nouveau programme on cree un nouveau maillon de pour notre liste
** au tout debut on a nb_programme == nb_champion
** le nombre de programme  en execution augmente lorsquon fait un fork
** (ou lfork je pense aussi)
*/

//void    fork(char *dir)
int     ft_fork(t_corevm *core, t_player *player)
{

}
