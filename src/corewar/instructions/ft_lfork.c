

#include "corewar.h"

/*
** 0x0f
** lfork -> long fork, meme chose que fork sans le % IDX_MOD
** lFork %34 crée un nouveau programme a (PC + 34)
** modifie le carry
** voir si comme on a pas le IDX_MOD on a pas dautre limitation quand meme genre
** % MEM_SIZE pour rester dans la memoire circulaire de notre core!!!
*/

//void	lfork(char *dir)
void	ft_lfork(t_corevm *vm, t_process *process)
{
	(void)vm;
	(void)process;
}
