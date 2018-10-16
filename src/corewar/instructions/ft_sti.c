

#include "corewar.h"

/*
** 0x0b
** sti -> va copier le 1er param dans une adresse obtenu grace au 2 autres params
** sti r2,%4,%5 -
** sti copies REG_SIZE octets de r2 a laddresse (4 + 5)
** ici les params 2 et 3 sont des index
** si ce sont des registres, on utilisera leur contenu comme un index
*/

//Usage : sti S(RG), S(RG/ID/D2), S(RG/D2)

void		ft_sti(t_corevm *vm, t_process *process)
{
	int	*values;
	int i;

	i = 0;
	get_args(vm, process, g_op_tab[process->type_instruc[0]]);
	ft_printf(" STORE INDIRECT process->args[0] d '%d'\n", process->args[0]);
	if (process->good_reg)
	{
		
		values = get_values(vm, process, 7, 0); //6 car on veux recup la valeur de 2 derniers arg
		//ft_memrev(&values[0], 4);
		if (values)
		{
			// ft_memrev(&values[0], 4);
			ft_printf(" STORE INDIRECT on copie ce param values[0] d '%d' '\n", values[0]);
			ft_printf(" ---STORE INDIRECT a ladresse de pc + values[1] %d values[2] int '%d'\n", (short)values[1],  (short)values[2]);
			ft_printf(" ---STORE INDIRECT a ladresse de pc + values[1] + values[2] int '%x'\n", (short)values[1] + (short)values[2]);

			
			// ft_printf("result values[1] + values[2] (690) %d\n", values[1] + values[2]);
			// ft_printf("result (values[1] + values[2]) %% IDX_MOD (178) %d\n", (values[1] + values[2]) % IDX_MOD);
			// ft_printf("result (((values[1] + values[2]) - 1 / IDX_MOD) & 1) (1) %d\n", (((values[1] + values[2] - 1) / IDX_MOD) & 1));
			// ft_printf("result nouveau calcul (-334) %d\n", (((values[1] + values[2]) % IDX_MOD) - IDX_MOD * (((values[1] + values[2] - 1) / IDX_MOD) & 1)));
			// ft_printf("result short %d\n", (process->pc + ((short)values[1] + (short)values[2]) % IDX_MOD) & (MEM_SIZE - 1));
			// ft_printf("result %d\n", (process->pc + (values[1] + values[2]) % IDX_MOD) & (MEM_SIZE - 1));
			int add = ((values[1] + values[2]) % IDX_MOD) - IDX_MOD * ((((values[1] + values[2]) / IDX_MOD) & 1) == (values[1] + values[2]) >= 0 ? 1 : 0 );
			ft_printf("add %d\n", add);
			ft_printf("((process->pc + add) & (MEM_SIZE - 1)) %d\n", ((process->pc + add) & (MEM_SIZE - 1)));
			*(int *)(vm->core + ((process->pc + add) & (MEM_SIZE - 1))) = values[0];
			// *(int *)(vm->core + ((process->pc + ((short)values[1] + (short)values[2]) % IDX_MOD) & (MEM_SIZE - 1))) = values[0];
	
			while (i < 4)
			{
				//revoir pour le CAST vm->color[(process->pc + (process->args[1] & (IDX_MOD - 1))) & (MEM_SIZE - 1)] = process->color;
			//	ft_printf("----------(process->pc + i + values[1] + values[2]) & (MEM_SIZE - 1) %d\n", (process->pc + i + values[1] + values[2]) & (MEM_SIZE - 1));
				vm->color[(process->pc + i + add) & (MEM_SIZE - 1)] = process->color + 4;
				i++;
			}
		//ft_printf(" STORE INDIRECT vm->core[(process->pc + values[1] + values[2]) & (MEM_SIZE - 1)] hexa '%x'\n", vm->core[(process->pc + values[1] + values[2]) & (MEM_SIZE - 1)]);
			free(values);
		}
	}
}