

#include "corewar.h"

/*
** 0x02
** ld -> load charge la valeur du 1er parametre dans le registre (2eme param)
** modifie le carry
** ld 34,r3 charge les REG_SIZE bytes (8bits) a partir de ladresse
** (PC + (34 % IDX_MOD)) ds le registre r3
** (IDX_MOD		(MEM_SIZE / 8))

Direct Load   0x02
Usage : ld S(ID/D4), D(RG)
Durée : 5    OCP : Oui
Adressage Restreint : Oui
Modifie le carry : Oui
Transfert direct RAM > Registre.
Charge le premier parametre dans le registre passé en
second parametre. Si la valeur du premier parametre
est egale a zero, alors le carry passe a l'etat un,
sinon a l'etat zero.
*/

void	ft_ld(t_corevm *vm, t_process *process)
{
	(void)vm;
	(void)process;
	/*if (process->type_instruc[1] == DIR_CODE) // sur 4 octets
	{
		process->reg[vm->core[(process->pc % MEM_SIZE) + 7] = (int)vm->core[(process->pc % MEM_SIZE) + 2]
	}
	if (process->type_instruc[1] == IND_CODE)
	{

	}*/
}
