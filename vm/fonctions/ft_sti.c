/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 10:10:15 by ccoupez           #+#    #+#             */
/*   Updated: 2018/07/12 16:46:12 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

/*
** 0x0b
** sti -> va copier le 1er param dans une adresse obtenu grace au 2 autres params
** sti r2,%4,%5 - 
** sti copies REG_SIZE octets de r2 a laddresse (4 + 5) 
** ici les params 2 et 3 sont des index
** si ce sont des registres, on utilisera leur contenu comme un index
*/

//void    sti(char *reg, char *reg_dir_ind, char *dir_reg)
int     ft_sti(t_corevm *core, t_players *players, t_instruction instruction)
{

}
