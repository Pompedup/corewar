

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
void	ft_and(t_corevm *vm, t_process *process)
{
	int	*values;

	if (!(test_args(process, g_op_tab[process->type_instruc[0]])))
		return ;
	get_args(vm, process, g_op_tab[process->type_instruc[0]]);

	values = get_values(vm, process, 3);
	printf("values[0] %d  values[1] %d\n", values[0], values[1]);
	if (values)
	{
		vm->info->first_processus->carry = (process->reg[process->args[2] - 1] = values[0] & values[1]) ? 1 : 0;//comme ca pour modifier le carry?
		// if (process->reg[process->args[2] - 1] == 0)//voir si ternaire
			// vm->info->first_processus->carry = 1;
		printf("process->reg[process->args[2] - 1] %d\n", process->reg[process->args[2] - 1]);
		free(values);
	}

}
