

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
	if (process->type_instruc[1] == 0xd0) //{T_IND, T_REG}
		get_two_octets(vm, process, 0);
	if (process->type_instruc[1] == 0x90) //{T_DIR, T_REG}
		get_four_octets(vm, process, 0);

	get_one_octet(vm, process, 1);
	//execute linstruction
}
