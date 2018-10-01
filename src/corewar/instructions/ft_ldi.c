

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
void	ft_ldi(t_corevm *vm, t_process *process)
{
	int	*values;
	int	s;

	if (!(test_args(process, g_op_tab[process->type_instruc[0]])))
		return ;
	get_args(vm, process, g_op_tab[process->type_instruc[0]]);

	values = get_values(vm, process, 3, 0);
	if (values)
	{
		s = values[0] + values[1];
		//REG_SIZE octets a ladresse (PC + (S % IDX_MOD))
		process->reg[process->args[2]] = vm->core[(process->pc
			+ (s % IDX_MOD)) % MEM_SIZE];
		free (values);
	}
}
