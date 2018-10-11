

#include "corewar.h"

/*
** 0x0d
** lld -> long long load, comme le load sans le % IDX_MOD
** charge la valeur du 1er parametre dans le registre (2eme param)
** lld 34,r3 charge les REG_SIZE bytes (8bits) a partir de ladresse
** (PC + 34) ds le registre r3
** voir si comme on a pas le IDX_MOD on a pas dautre limitation
** quand meme genre
** % MEM_SIZE pour rester dans la memoire circulaire de notre core!!!
** modifie le carry
*/

//Usage : lld S(ID/D4), D(RG)
void		ft_lld(t_corevm *vm, t_process *process)
{
	int	*values;
	//ft_printf(" DANS LLD process->type_instruc[1] hexa  %x\n", process->type_instruc[1]);
	get_args(vm, process, g_op_tab[process->type_instruc[0]]);

	values = get_values(vm, process, 1, 1); //1 on recupere seulement la valeur de larg 1

	//ft_printf(" ---------LONG LOAD values[0] hexa %x\n", values[0]);
	if (values)
	{
		process->reg[process->args[1]] = values[0];
		process->carry = values[0] == 0 ? 1 : 0; //MODIFIE LE CARRY ????!!!!!
		free(values);
	}
}
