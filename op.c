/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adibou <adibou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2018/07/12 11:04:56 by adibou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

t_op    op_tab[17] =
{
1	{"live",	1, {T_DIR}, 												1, 	10, 		"alive",								0, 0},
2	{"ld", 		2, {T_DIR | T_IND, T_REG}, 									2, 	5, 			"load", 								1, 0},
3	{"st",		2, {T_REG, T_IND | T_REG}, 									3, 	5, 			"store", 								1, 0},
4	{"add",		3, {T_REG, T_REG, T_REG}, 									4, 	10, 		"addition", 							1, 0},
5	{"sub",		3, {T_REG, T_REG, T_REG}, 									5, 	10, 		"soustraction", 						1, 0},
6	{"and",		3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 	6, 	6, 			"et (and  r1, r2, r3   r1&r2 -> r3", 	1, 0},
7	{"or",		3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 	7, 	6, 			"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
8	{"xor",		3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 	8, 	6, 			"ou (xor  r1, r2, r3   r1^r2 -> r3", 	1, 0},
9	{"zjmp",	1, {T_DIR},													9, 	20, 		"jump if zero", 						0, 1},
a	{"ldi",		3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 			10, 25, 		"load index", 							1, 1},
b	{"sti",		3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 			11, 25, 		"store index", 							1, 1},
c	{"fork",	1, {T_DIR}, 												12, 800, 		"fork", 								0, 1},
d	{"lld",		2, {T_DIR | T_IND, T_REG},									13, 10, 		"long load", 							1, 0},
e	{"lldi",	3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 			14, 50, 		"long load index", 						1, 1},
f	{"lfork",	1, {T_DIR},													15, 1000, 		"long fork", 							0, 1},
a0	{"aff",		1, {T_REG},													16, 2, 			"aff", 									1, 0},
	{0, 0, {0}, 0, 0, 0, 0, 0}
};

[instruction][format][data]


1	x 01 (int)xxxx xxxx

2	x 02 (jesaispaspourquoi) 90 (int)xxxx xxxx (r)xx
ld		[type]	:buff,			r1
02		d0 		003f			01
ld		[type]	%4,				r4
02		90 		0000 0004		04


3	x 03 xxxx xxxx
st 		[type]	r1,				:buff
03		70		01				0049
st		[type]	r1,				r1
03		50		01				01


4	x 04 (indice sur le nombre de bits a lire ?)xx (r1) xx (r2)xx (r3)xx
add		[type]	r3,		r4,		r3
04		54		03		04		03


5	x 05 (indice sur le nombre de bits a lire ?)xx (r1) xx (r2)xx (r3)xx
sub		[type]	r3,		r4,		r3
05		54		03		04		03


6	x 06 (indice sur le nombre de bits a lire ?)xx (r1) xx (int)xxxx xxxx (r3)xx
and		[type]	r6,		%2147483648,	r8
06		64 		06		80000000		08


7	x 07
or		[type]	r2,		r2,		r2
07		54		02		02		02


8	x 08 (indice sur le nombre de bits a lire ?)xx (r1) xx (int)xxxx xxxx (r3)xx
xor		[type]	r5,		r3,		r6
08		54		05		03		06


9	x 09 (adresse ff ou nombre 00)xx (l adresse ou le nombre)xx
zjmp 	%-207
09		ff31
zjmp	%:suite
09		0037


a	x 0a xxxx xxxx xx
ldi     [type]	%:copie,	%3,		r2
0a		a4 		0146		0003	02
ldi 	[type]	%-5,		r3,		r1
0a		94 		fffb 		03		01


b	x 0b (68) xxxx xxxx xxxx (64) xxxx xxxx
sti 	[type]	r1,		%:boucle,%25
0b		68 		01		000700 	19
sti 	[type]	r1,		%17,	r3
0b		64 		01		0011	03
sti		[type]	r7,		r9,		r6
0b		54		07		08		06


c	x 0c xxxx
fork	%:live0
0c		ffd3


d	x 0d
e	x 0e
f	x 0f
10	x 10
