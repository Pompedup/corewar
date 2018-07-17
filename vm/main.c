/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 13:17:29 by ccoupez           #+#    #+#             */
/*   Updated: 2018/07/17 15:29:49 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int     main(int ac, char **av)
{
    t_corevm    vm;

    //get argument
    init_vm(av, &vm);
    parse_argv(&vm);
    //parse flag -dump, -visualisateur -n num champion ...
    //parse les fichier 
	//place_champions()
	//start_the_battle()
    printf("main vm.dump %d\n", vm.dump);
    printf("main vm.nb_players %d\n", vm.nb_players);
    printf("main vm.visu %d\n", vm.visu);
    printf("main vm.players[0]->num %d\n", vm.players[0]->num);
    printf("main vm.players[0]->file -%s-\n", vm.players[0]->file);
    printf("main vm.players[1]->num %d\n", vm.players[1]->num);
    printf("main vm.players[1]->file -%s-\n", vm.players[1]->file);
    return (0);
}