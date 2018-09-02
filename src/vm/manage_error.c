/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 18:32:47 by ccoupez           #+#    #+#             */
/*   Updated: 2018/09/02 16:26:52 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** file_name is not a corewar executable
*/

/*
** prog number num already used
*/

/*
** file file_name not accessible
*/

/*
** can't perform malloc
*/


/*
** can't perform open - read - close
*/

void     ft_error(t_corevm *vm, int num_error)
{
    (void)vm;
    (void)num_error;
    //free toute la vm
    //print message d'erreur
    printf("error %d\n", num_error);
    exit(0);
}

void    ft_read_error(t_corevm *vm, int num_error, int fd)
{
    (void)fd;
    if (close(fd) == -1)
		ft_error(vm, num_error); //close error :'(
	ft_error(vm, -3); // num error probleme de lecture!!!
}
/*
** a free : les players (nb_players) - les headers des player (nb_players)
** je crois que cest tout pour le moment :D !!!
*/
