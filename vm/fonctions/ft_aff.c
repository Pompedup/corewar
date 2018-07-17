/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 10:13:25 by ccoupez           #+#    #+#             */
/*   Updated: 2018/07/12 16:45:52 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

/*
** 0x10
** aff -> Elle prend en paramètre un registre 
** et affiche le caractère dont le code ascii est présent dans ce registre
** (un modulo 256 est applique au code ascii, 
** le caractère est affiché sur la sortie standard) 
** Ex: ld %52,r3 
** aff r3 
** affiche '*' sur la sortie standard
*/

//void	aff(char *reg)
int     ft_aff(t_corevm *core, t_players *players, t_instruction instruction)
{

}   