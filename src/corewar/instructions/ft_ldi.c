

#include "corewar.h"

/*
** 0x0a
** modifie le carry
** ldi -> load a l'indice
** ex : ldi 3,%4,r1
** lit IND_SIZE octets a ladresse: (PC + (3 % IDX_MOD)),
** ajoute 4 a cette valeur

** on nomme cette somme S.

** on lit REG_SIZE octets a ladresse (PC + (S % IDX_MOD)),

** quon copie dans r1
** les parametres 1 et 2 sont des index.
*/

//Usage : ldi S(RG/ID/D2), S(ID/D2), D(RG)
void		ft_ldi(t_corevm *vm, t_process *process)
{
	int	*values;
	// int	s;

	//ft_printf(" ---------LOAD INDICE  \n");
	get_args(vm, process, g_op_tab[process->type_instruc[0]]);
	//ft_printf(" ---------LOAD INDICE  process->args[0]d %d \n", process->args[0]);
	//ft_printf(" ---------LOAD INDICE  process->args[1] d %d \n", process->args[1]);
	//ft_printf(" ---------LOAD INDICE  reg de stock final  %d \n", process->args[2]);
	if (process->good_reg)
	{
		values = get_values(vm, process, 3, 0);
		//ft_printf(" ---------LOAD INDICE values[0] d %d --values[1] d %d \n", values[0], values[1]);
		//ft_printf(" ---------LOAD INDICE values[0] + values[1] - d %d \n", values[0] + values[1]);
		if (values)
		{
			// s = values[0] + values[1];

			// ft_printf("result %d\n", (process->pc + (s % IDX_MOD)) & (MEM_SIZE - 1));
			// process->reg[process->args[2]] = *((int *)(vm->core + ((process->pc + (s % IDX_MOD )) & (MEM_SIZE - 1))));
			int add = ((values[0] + values[1]) % IDX_MOD) - IDX_MOD * ((((values[0] + values[1]) / IDX_MOD) & 1) == (values[0] + values[1]) >= 0 ? 1 : 0 );
			//ft_printf("result %d\n", (process->pc + add) & (MEM_SIZE - 1));
			//ft_printf("result (values[0] + values[1]) %d\n", (values[0] + values[1]));
			//ft_printf("result add %d\n", add);
			process->reg[process->args[2]] = *((int *)(vm->core + ((process->pc + add) & (MEM_SIZE - 1))));
		//	ft_memrev(&process->reg[process->args[2]], 4);
			process->carry = (process->reg[process->args[2]]) ? 0 : 1;
				//ft_printf(" ---------LOAD INDICE process->reg[process->args[2]] hexa %x\n", process->reg[process->args[2]]);
			//	ft_printf(" ---------LOAD INDICE reg final x %x\n", process->reg[process->args[2]]);
			//	ft_printf(" ---------LOAD INDICE reg final d %d\n", process->reg[process->args[2]]);
			//	ft_memrev(&process->reg[process->args[2]], 4);
			//	ft_printf(" ---------LOAD INDICE reg final revvv x %x\n", process->reg[process->args[2]]);
			//	ft_printf(" ---------LOAD INDICE reg final revvv d %d\n", process->reg[process->args[2]]);
			//	ft_memrev(&process->reg[process->args[2]], 4);
			free (values);
		}
	}
}
