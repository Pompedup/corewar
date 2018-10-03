/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecesari <ecesari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 13:17:29 by ccoupez           #+#    #+#             */
/*   Updated: 2018/10/03 13:04:35 by ecesari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int	check_include(void)
{
	long long	inc;
	int			nb_one;

	inc = 1;
	nb_one = 0;
	if (!MEM_SIZE && MEM_SIZE > SHORT)
		return (0);
	while (inc < SHORT && inc <= MEM_SIZE)
	{
		if ((MEM_SIZE & inc) != 0)
			nb_one++;
		inc = inc * 2;
	}
	if (nb_one != 1)
		return (0);
	return (1);
}

int     main(int ac, char **av)
{
	t_corevm    vm;
	// t_player	*tmp;

	(void)av;
	if (ac < 2)
		ft_error(&vm, ERR_MESS_0, 0);
	if (!check_include())
		ft_error(&vm, ERR_MESS_00, 0);
	ft_printf("ok memsize\n");
	// init_vm(av, &vm);
	// parse_argv(&vm);
	// number_players(&vm);
	// players_charged_in_core(&vm);
	// execute_the_battle(&vm); // !!!!!! :D (ง •̀_•́)ง  ᕙ༼*◕_◕*༽ᕤ


	//dump the core and print the winner ( ˘ ³˘)♥ ♥ ♥ ♥
	// tmp = vm.info->first_player;
	//printf("main vm.dummp %d\n", vm.dump);
	//int i = 0;
	//while (tmp)
	//{
	//	printf("%d : main tmp->name_file %s\n", i, tmp->name_file);
	//	printf("%d : main tmp->num %d\n", i, tmp->num);
	//   	// printf("     main tmp->len_file %d\n", tmp->len_file);
	//	tmp = tmp->next;
	//	i++;
	//}
	return (0);
}

/*
** le parallelisme : A chaque cycle, toutes les opérations vont être executées comme si elles
avaient lieu exactement en même temps. Cela a une influence sur les signaux de vie et les écritures
en mémoire
Ecritures simultanées en mémoire : que se passe-t-il lorsque plusieurs processeurs écrivent
en mémoire au même endroit au même moment ? Pour respecter le parallélisme, un système de votes a
été mis en place. Si un même quartet de la mémoire est affecté plusieurs fois au cours d'un même
cycle, il y a un vote indépendant pour chacun des bits du quartet. Si l'on cherche à écrire plus
de fois 0 que 1, un 0 est écrit, si l'on cherche à écrire plus de fois 1 que 0, un 1 est écrit,
et s'il y a ballotage, la valeur actuelle du bit est conservée. C'est aussi simple que cela.
*/
