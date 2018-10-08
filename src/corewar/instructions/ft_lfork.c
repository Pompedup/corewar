

#include "corewar.h"

/*
** 0x0f
** lfork -> long fork, meme chose que fork sans le % IDX_MOD
** lFork %34 crée un nouveau programme a (PC + 34)
** modifie le carry
** voir si comme on a pas le IDX_MOD on a pas dautre limitation quand meme genre
** % MEM_SIZE pour rester dans la memoire circulaire de notre core!!!
*/

//Usage : lfork S(D2)
int		ft_lfork(t_corevm *vm, t_process *process)
{

	t_player	*tmp;
	t_process	*fork;

	tmp = vm->info->first_player;
	fork = NULL;
		ft_printf("_____________________test LONG fork\n");
	get_two_octets(vm, process, 0);
	while (ft_strcmp(process->name, tmp->header->prog_name) && tmp)
	{
		printf("test\n");
		tmp = tmp->next;
	}
	if (tmp)
	{
		fork = create_process(vm, (process->pc + (process->args[0])), tmp);
	}
	put_process_front(&vm->info->first_processus, fork);
	while (fork)
	{
		ft_printf("YOU LFORK IT!\n, fork->pc %d \n", fork->pc);
		fork = fork->next;
	}
	// vm->core[(process->pc + (process->args[0] % IDX_MOD)) % MEM_SIZE] =
	//un nouveau programme herite des differents etats du pere;
	return (1);
}
