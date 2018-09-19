

#include "corewar.h"

/*
** 0x0b
** sti -> va copier le 1er param dans une adresse obtenu grace au 2 autres params
** sti r2,%4,%5 -
** sti copies REG_SIZE octets de r2 a laddresse (4 + 5)
** ici les params 2 et 3 sont des index
** si ce sont des registres, on utilisera leur contenu comme un index
*/

//Usage : sti S(RG), S(RG/ID/D2), S(ID/D2)
void	ft_sti(t_corevm *vm, t_process *process)
{
	static unsigned int	key_tab[6] = {0x58, 0x54, 0x68, 0x64, 0x78, 0x74};

	if (is_in_key_tab(process->type_instruc[1], key_tab, 6))
		get_one_octet(vm, process, 0);

	if (process->type_instruc[1] == 54 || process->type_instruc[1] == 58)
		get_one_octet(vm, process, 1);
	else if (is_in_key_tab(process->type_instruc[1], key_tab + 2, 4))
		get_two_octets(vm, process, 1);

	if (process->type_instruc[1] == 54 || process->type_instruc[1] == 64
		|| process->type_instruc[1] == 74)
		get_one_octet(vm, process, 2);
	if (process->type_instruc[1] == 58 || process->type_instruc[1] == 68
		|| process->type_instruc[1] == 78)
		get_two_octets(vm, process, 2);

	//execute linstruction
}
