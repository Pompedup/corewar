/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_zjump.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 10:13:08 by ccoupez           #+#    #+#             */
/*   Updated: 2018/07/18 15:07:43 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

/*
** 0x09 
** jump -> fait un saut à l'adresse passée en parametre
** SI le carry est a 1
** si le carry nest pas a 1 il ne fait rien mais consomme le meme temps
** zjmp %23 -
** si carry == 1 -
** met (PC + (23 % IDX_MOD)) DANS le PC
** on fait faire un saut a notre pointeur sur processus 
** pour quil aille a un autre endroit de notre p    rogramme et continue de lire 
** les instruction depuis cette nouvelle adresse
*/

//void	zjump(char *dir)
int     ft_zjump(t_corevm *core, t_player *player)
{

}
