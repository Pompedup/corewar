/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 18:32:47 by ccoupez           #+#    #+#             */
/*   Updated: 2018/07/20 14:24:05 by ccoupez          ###   ########.fr       */
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
    printf("eroor %d\n", num_error);
    exit(0);
}


/*
** a free : les players (nb_players) - les headers des player (nb_players)
** je crois que cest tout pour le moment :D !!!
*/