

#include "corewar.h"

/*
** 0x03
** st -> store, met la valeur du 1er arg(un registre) dans le 2eme
** st 34, r3 - charge les REG_SIZE octets a partir de ladresse
** ( PC + (34 % IDX_MOD))
** ou st r3, r8 - copie r3 dans r8
*/

//void	st(char *reg, char *ind_reg)
void	ft_st(t_corevm *vm, t_process *process)
{
	(void)vm;
	(void)process;
}
