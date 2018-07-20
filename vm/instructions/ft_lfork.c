/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lfork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 10:11:44 by ccoupez           #+#    #+#             */
/*   Updated: 2018/07/18 15:06:51 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

/*
** 0x0f
** lfork -> long fork, meme chose que fork sans le % IDX_MOD
** lFork %34 crée un nouveau programme a (PC + 34)
** modifie le carry
** voir si comme on a pas le IDX_MOD on a pas dautre limitation quand meme genre 
** % MEM_SIZE pour rester dans la memoire circulaire de notre core!!!
*/

//void	lfork(char *dir)
int     ft_lfork(t_corevm *core, t_player *player)
{

}
