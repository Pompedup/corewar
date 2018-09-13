

#include "corewar.h"

/*
** 0x0d
** lld -> long long load, comme le load sans le % IDX_MOD
** charge la valeur du 1er parametre dans le registre (2eme param)
** lld 34,r3 charge les REG_SIZE bytes (8bits) a partir de ladresse
** (PC + 34) ds le registre r3
** voir si comme on a pas le IDX_MOD on a pas dautre limitation quand meme genre
** % MEM_SIZE pour rester dans la memoire circulaire de notre core!!!
** modifie le carry
*/

//Usage : lld S(ID/D4), D(RG)
void	ft_lld(t_corevm *vm, t_process *process)
{
	(void)vm;
	(void)process;
}
