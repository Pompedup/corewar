/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 10:09:09 by ccoupez           #+#    #+#             */
/*   Updated: 2018/07/18 15:07:19 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

/*
** 0x03
** st -> store, met la valeur du 1er arg(un registre) dans le 2eme
** st 34, r3 - charge les REG_SIZE octets a partir de ladresse
** ( PC + (34 % IDX_MOD))
** ou st r3, r8 - copie r3 dans r8  
*/

//void	st(char *reg, char *ind_reg)
int     ft_st(t_corevm *core, t_player *player)
{

}
