

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
	(void)vm;

	if (process->type_instruc[1] == DIR_CODE
		&& process->type_instruc[2] == REG_CODE
			&& process->type_instruc[3] == 0
				&& && process->type_instruc[4] == 0) // 1er arg sur 4 octets
	{
		//ici executer laction ld avec un direct
		process->pc += 7;
	}
	else if (process->type_instruc[1] == IND_CODE
				&& process->type_instruc[2] == REG_CODE
					&& process->type_instruc[3] == 0
						&& process->type_instruc[4] == 0) // 1er arg sur 2 octets
	{
		//ici executer laction ld avec un indirect
		process->pc += 5;
	}
	else
		//instruction compromise les arg ne sont pas bon on execute rien


}
//il doit y avoir plus opti pour checker les agr et savoir quoi faire
