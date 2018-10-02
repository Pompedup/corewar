

#include "corewar.h"

extern t_op	g_op_tab[];

/*
********************************************************************************
** 0x06
** Applique un & (ET bit-à-bit) sur les deux premiers paramètres, et stocke le
résultat dans le registre qui est le 3ème paramètre. Opcode 0x06. Modifie le carry.
** ET bit à bit : l'arg1 & l'arg2 et met le resultat dans l'arg3
** and r2,%0,r3 - met r2 & 0 dans r3
** modifie le carry
** Si la valeur resultante est egale a zero, alors le carry passe a l'etat un, sinon a l'etat zero
********************************************************************************
*/

//Usage : and S(RG/ID/D4), S(RG/ID/D4), D(RG)
int		ft_and(t_corevm *vm, t_process *process)
{
	int	*values;

	if (!(test_args(process, g_op_tab[process->type_instruc[0]])))
		return (0);
	get_args(vm, process, g_op_tab[process->type_instruc[0]]);

	values = get_values(vm, process, 3, 0);
	printf(" AND values[0] hexa %x  values[1] hexa %x\n", values[0], values[1]);
	if (values)
	{
		process->reg[process->args[2] - 1] = values[0] & values[1];
		process->carry = (process->reg[process->args[2]]) ? 0 : 1;//comme ca pour modifier le carry?
		printf("process->reg[process->args[2] - 1] hexa %x\n", process->reg[process->args[2] - 1]);
		free(values);
	}
	return (1);
}
