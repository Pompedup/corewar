/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecesari <ecesari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 18:32:47 by ccoupez           #+#    #+#             */
/*   Updated: 2018/09/25 12:31:39 by ecesari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

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

void     ft_error(t_corevm *vm, char *mess_error, int to_free)
{
    (void)vm;
    ft_fprintf(2, "Error: %s.\n", mess_error);
    if (to_free)
        ft_strdel(&mess_error);
    //free toute la vm
    exit(0);
}

/*
** can't perform open - read - close
*/

void    ft_read_error(t_corevm *vm, char *mess_error, int fd)
{
    if (close(fd) == -1)
		ft_error(vm, ft_strjoin(ERR_MESS_6, ft_itoa(fd)), 1);//of file fd
    ft_error(vm, ft_strjoin(mess_error, ft_itoa(fd)), 1);
}

/*
** a free : les players (nb_players) - les headers des player (nb_players)
** je crois que cest tout pour le moment :D !!!
*/



/*
** -dump nbr_cycles Au bout de nbr_cycles cycles d’exécution,
** dump la mémoire sur la sortie standard, puis quitte la partie.
** La mémoire doit être dumpée au format hexadécimal, avec 32 octets par ligne.
*/

void	ft_dump_exit(t_corevm *vm)
{
    (void)vm;
}
