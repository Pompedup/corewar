

#include "corewar.h"

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

//Usage : lldi S(RG/ID/D2), S(ID/D2), D(RG)
void	ft_lldi(t_corevm *vm, t_process *process)
{
	int	*values;
	int	s;

	//ft_printf(" ---------LONG LOAD INDICE  \n");
	get_args(vm, process, g_op_tab[process->type_instruc[0]]);
	if (process->good_reg)
	{
		values = get_values(vm, process, 3, 1);
		//ft_printf(" ---------LONG LOAD INDICE values[0] hexa %x -- hexa %x \n", values[0], values[1]);
		//ft_printf(" ---------LONG LOAD INDICE values[0] d %d -- d %d \n", values[0], values[1]);
		if (values)
		{
			s = values[0] + values[1];
			process->reg[process->args[2]] = (char)(vm->core[((process->pc)
				+ s) & (MEM_SIZE - 1)]);
			process->carry = (process->reg[process->args[2]]) ? 0 : 1;
				//ft_printf(" ---------LONG LOAD INDICE values[0] hexa %x\n", process->reg[process->args[2]]);
				//ft_printf(" ---------LONG LOAD INDICE reg final d %d\n", process->reg[process->args[2]]);
			free (values);
		}
	}
}
