

#include "op.h"

/*
** 0x0e
** lldi -> long long load indice, comme le load indice sans le % IDX_MOD
** ex : lldi 3,%4,r1 
** lit IND_SIZE octets a ladresse: (PC + 3), 
** ajoute 4 a cette valeur
** on nomme cette somme S. 
** on lit REG_SIZE octets a ladresse (PC + S ), 
** quon copie dans r1
** les parametres 1 et 2 sont des index.
** voir si comme on a pas le IDX_MOD on a pas dautre limitation quand meme genre 
** % MEM_SIZE pour rester dans la memoire circulaire de notre core!!!
** modifie le carry
*/

//void	lldi(char *reg_dir_ind, char *dir_reg, char *reg)
int     ft_lldi(t_corevm *core, t_player *player)
{

}
