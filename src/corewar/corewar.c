/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 13:17:29 by ccoupez           #+#    #+#             */
/*   Updated: 2018/09/13 14:49:38 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int     main(int ac, char **av)
{
	t_corevm    vm;
	t_player	*tmp;

	if (ac < 2)
		ft_error(&vm, 0); //// no emought argv - usage: ./corewar [-dump nbr_cycles] [[-n number] champion1.cor] ...
	init_vm(av, &vm);
	parse_argv(&vm);
	number_players(&vm);
	players_charged_in_core(&vm);
	execute_the_battle(&vm); // !!!!!! :D (ง •̀_•́)ง  ᕙ༼*◕_◕*༽ᕤ


	//dump the core and print the winner ( ˘ ³˘)♥ ♥ ♥ ♥
	tmp = vm.info->first_player;
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
A faire pour lexecution de la battle :D

• La machine virtuelle va créer un espace mémoire,
et  exécuter séquentiellement (parrallement) les champions

• Tous les CYCLE_TO_DIE cycles, s’assurer que chaque processus
a exécuté au moins un live depuis la dernière vérif. Un processus qui ne se
soumet pas à cette règle sera mis à mort à l’aide d’une batte en mousse virtuelle.
(Bonus bruitage !)

• Si au cours d’une de ces vérifications on se rend compte qu’il y a eu au moins
NBR_LIVE exécutions de live depuis la dernière vérification en date, on décrémente
CYCLE_TO_DIE de CYCLE_DELTA unités.

• Le gagnant est le dernier joueur qui a été rapporté comme étant en vie.
La machine va ensuite afficher : "le joueur x(nom_champion) a gagne", où x est le numéro
du joueur et nom_champion le nom de son champion.
Exemple : "le joueur 2(rainbowdash) a gagne"

• A chaque exécution valide de l’instruction live, la machine doit afficher :
"un processus dit que le joueur x(nom_champion) est en vie"

• En tout état de cause, la mémoire est circulaire et fait MEM_SIZE octets.

• En cas d’erreur, vous devrez afficher un message pertinent sur la sortie d’erreur.

• Si on n’a pas décrémenté CYCLE_TO_DIE depuis MAX_CHECKS vérifications,
on le décrémente.
*/

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
