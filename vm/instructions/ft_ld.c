/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 10:08:49 by ccoupez           #+#    #+#             */
/*   Updated: 2018/07/18 15:06:38 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

/*
** 0x02
** ld -> load charge la valeur du 1er parametre dans le registre (2eme param)
** modifie le carry
** ld 34,r3 charge les REG_SIZE bytes (8bits) a partir de ladresse
** (PC + (34 % IDX_MOD)) ds le registre r3 
** (IDX_MOD		(MEM_SIZE / 8))
*/

//void	ld(char *dir_ind, char *reg)
int     ft_ld(t_corevm *core, t_player *player)
{
    
}
