/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lld.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 10:10:54 by ccoupez           #+#    #+#             */
/*   Updated: 2018/07/18 15:07:02 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

/*
** 0x0d
** lld -> long long load, comme le load sans le % IDX_MOD
** charge la valeur du 1er parametre dans le registre (2eme param)
** lld 34,r3 charge les REG_SIZE bytes (8bits) a partir de ladresse
** (PC + 34) ds le registre r3
** voir si comme on a pas le IDX_MOD on a pas dautre limitation quand meme genre 
** % MEM_SIZE pour rester dans la memoire circulaire de notre core!!!
** modifie le carry
*/

//void	lld(char *dir_ind, char *reg)
int     ft_lld(t_corevm *core, t_player *player)
{

}
