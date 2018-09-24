

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

ld : Prend un paramètre quelconque et un registre. Charge la valeur
du premier paramètre dans le registre. Son opcode est 10 en binaire,
et il changera le carry.
*/

//Usage : ld S(ID/D4), D(RG)
void	ft_ld(t_corevm *vm, t_process *process)
{
	int	*values;

	if (g_op_tab[process->type_instruc[0]].nbr_arg > 1)
		if (!(test_args(process, g_op_tab[process->type_instruc[0]])))
			return ;
	get_args(vm, process, g_op_tab[process->type_instruc[0]]);

	values = get_values(vm, process, 1); //1 on recupere seulement la valeur de larg 1

	if (values)
	{
		process->reg[process->args[1]] = values[0];
		process->carry = values[0] = 0 ? 1 : 0; //MODIFIE LE CARRY ????!!!!!
	}



	free(values);

}
