    /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 10:09:39 by ccoupez           #+#    #+#             */
/*   Updated: 2018/07/10 15:06:12 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

/*
** 0x0a
** modifie le carry
** ldi -> load a l'indice
** ex : ldi 3,%4,r1 
** lit IND_SIZE octets a ladresse: (PC + (3 % IDX_MOD)), 
** ajoute 4 a cette valeur
** on nomme cette somme S. 
** on lit REG_SIZE octets a ladresse (PC + (S % IDX_MOD)), 
** quon copie dans r1
** les parametres 1 et 2 sont des index.
*/

//void    ldi(char *reg_dir_ind, char *dir_reg, char *reg)
int     ft_ldi(t_corevm *core, t_players *players, t_instruction instruction)
{

}