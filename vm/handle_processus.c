/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_processus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 15:13:34 by ccoupez           #+#    #+#             */
/*   Updated: 2018/08/31 15:37:49 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "vm.h"

/*void        put_process_first(t_corevm *vm, t_process *process)
{

}*/

t_process	*create_processus(t_corevm *vm, char *pc, t_player *player)
{
    int         i;
    t_process   *process;

    if (!(process = malloc(sizeof(t_process))))
        ft_error(vm, -66); //malloc error
    process->color = player->color;
    process->pc = NULL;
	process->carry = 0;
	process->reg[0] = player->num;
	i = 1;
	while (i < REG_NUMBER)
		process->reg[i++] = 0;
}
