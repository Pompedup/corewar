/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 13:17:29 by ccoupez           #+#    #+#             */
/*   Updated: 2018/07/20 16:05:09 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int     main(int ac, char **av)
{
	int i = 0;
	t_corevm    vm;
	t_player	*tmp;	
	init_vm(av, &vm);
	parse_argv(&vm);
	number_players(&vm);
	charge_players_in_core(&vm);
	//start_the_battle(); !!!!!!

	tmp = vm.info_players->first;
	while (tmp)
	{
		printf("%d : main tmp->name_file %s\n", i, tmp->name_file);
		printf("%d : main tmp->num %d\n", i, tmp->num);
	   	// printf("     main tmp->len_file %d\n", tmp->len_file);
		tmp = tmp->next;
		i++;
	}
	return (0);
}

/*
A faire pour lexecution de la battle :D

• La machine virtuelle va créer un espace mémoire dédié au combat des joueurs, puis
y charger les champions et leurs processus associés, et les exécuter séquentiellement (parrallement)
jusqu’à ce que mort s’ensuive.

• Tous les CYCLE_TO_DIE cycles, la machine doit s’assurer que chaque processus
a exécuté au moins un live depuis la dernière vérification. Un processus qui ne se
soumet pas à cette règle sera mis à mort à l’aide d’une batte en mousse virtuelle.
(Bonus bruitage !)

• Si au cours d’une de ces vérifications on se rend compte qu’il y a eu au moins
NBR_LIVE exécutions de live depuis la dernière vérification en date, on décrémente
CYCLE_TO_DIE de CYCLE_DELTA unités.

• Quand il n’y a plus de processus en vie, la partie est terminée.

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