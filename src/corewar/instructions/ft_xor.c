

#include "corewar.h"

/*
** 0x08
** ou exclusif
** XOR bit à bit :   l'arg1 | l'arg2 et met le resultat dans l'arg3
** modifie le carry
*/

//Usage : xor S(RG/ID/D4), S(RG/ID/D4), D(RG)
void		ft_xor(t_corevm *vm, t_process *process)
{
	int	*values;

	get_args(vm, process, g_op_tab[process->type_instruc[0]]);

	if (process->good_reg)
	{

		ft_printf(" XOR process->args[0] d %d  process->args[1] d %d process->args[2] d %d\n", process->args[0], process->args[1], process->args[2]);
		values = get_values(vm, process, 3, 0);
		ft_printf(" XOR values[0] hexa %x  values[1] hexa %x\n", values[0], values[1]);
		if (values)
		{
			process->reg[process->args[2]] = values[0] ^ values[1];
			process->carry = (process->reg[process->args[2]]) ? 0 : 1;//comme ca pour modifier le carry?

			ft_printf("process->reg[process->args[2]]%d\n", process->reg[process->args[2]]);
			ft_printf("process->carry %d\n", process->carry);
			//ft_printf("\tXOORRR   process->args[2] hexa '%x'\n", process->args[2]);
			//ft_printf("process->reg[process->args[2]] hexa %x\n", process->reg[process->args[2]]);
			free(values);
		}
	}
}
