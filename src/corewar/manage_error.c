/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecesari <ecesari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 18:32:47 by ccoupez           #+#    #+#             */
/*   Updated: 2018/10/08 13:29:41 by ecesari          ###   ########.fr       */
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
********************************************************************************
** ft_error
**  can't perform open - read - close
********************************************************************************
*/

void     ft_error(t_corevm *vm, char *mess_error, int to_free)
{
    (void)vm;
    if (ft_strstr(mess_error, ERR_MESS_11))
        ft_fprintf(2, "Error: File %s (%d bytes > %d bytes).\n", mess_error, vm->info->first_player->header->prog_size, CHAMP_MAX_SIZE);
    else
        ft_fprintf(2, "Error: %s.\n", mess_error);
    if (to_free)
        ft_strdel(&mess_error);
    //free toute la vm
    exit(0);
}

/*
********************************************************************************
** ft_read_error
********************************************************************************
*/

void    ft_read_error(t_corevm *vm, char *mess_error, int fd)
{
    if (close(fd) == -1)
		ft_error(vm, ft_strjoin(ERR_MESS_6, vm->info->first_player->name_file), 1);
    ft_error(vm, mess_error, 1);
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
