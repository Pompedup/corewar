/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecesari <ecesari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 21:06:11 by abezanni          #+#    #+#             */
/*   Updated: 2018/10/09 17:04:26 by ecesari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "corewar.h"

t_op	g_op_tab[] =
{
	{"live",  1, {T_DIR}, 1, 10, 				"alive", 								0, 0},
	{"ld",    2, {T_DIR | T_IND, T_REG}, 2, 5, 	"load", 								1, 0},
	{"st",    2, {T_REG, T_IND | T_REG}, 3, 5, 	"store", 								0, 0},
	{"add",   3, {T_REG, T_REG, T_REG}, 4, 10, 	"addition", 							1, 0},
	{"sub",   3, {T_REG, T_REG, T_REG}, 5, 10, 	"soustraction", 						1, 0},
	{"and",   3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,	"et", 	1, 0},
	{"or",    3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6, 	"ou", 	1, 0},
	{"xor",   3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6, 	"xou",	1, 0},
	{"zjmp",  1, {T_DIR}, 9, 20, 				"jump if zero",							0, 1},
	{"ldi",   3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,			"load index",	1, 1},
	{"sti",   3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,			"store index", 	0, 1},
	{"fork",  1, {T_DIR}, 12, 800,				 "fork", 								0, 1},
	{"lld",   2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 							1, 0},
	{"lldi",  3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,			"long load 	index",	1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, 			"long fork", 							0, 1},
	{"aff",   1, {T_REG}, 16, 2, 				"aff", 									1, 0},
	{0, 0, {0}, 0, 0, 0, 0, 0},
};

/*
{shortcut, nbr_arg, accept[], id (=opcode), nb_cycle_instruction, descirption, ind(qui modifie carry), dir(4 ou 2)}
typedef struct		s_op
{
	char			*shortcut;
	int				nbr_arg; // 1 || 2 || 3
	char			accept[3];
	int				id;//opcode
	int				nb_cycle_instruction; //10 || 5 || 6 || 20 || 25 || 800 || 1000
	char			*description;
	int				ind;//a renommer en flag_carry (si l'instruction modifie le carry flag actif)
//verifier aue pour ld le carry passe a 0 si la valeur ld est != 0 et a 1 si la valeur de ld est == 0
//verifier pour le st et le sti
	int				dir;
	}					t_op;
*/

/*
{T_REG | T_DIR | T_IND,  1 | 2 | 4 -> 00 00 01 11

T_REG | T_IND | T_DIR,

T_REG}
*/



/*

	{"live",  1, {T_DIR}, 1, 10, 				"alive", 								0, 0},
	{"zjmp",  1, {T_DIR}, 9, 20, 				"jump if zero",							0, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, 			"long fork", 							0, 1},
	{"fork",  1, {T_DIR}, 12, 800,				 "fork", 								0, 1},



	{"ld",    2, {T_DIR | T_IND, T_REG}, 2, 5, 	"load", 								1, 0},  --> +2
	{"st",    2, {T_REG, T_IND | T_REG}, 3, 5, 	"store", 								0, 0},	--> +2
	{"lld",   2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 							1, 0},	--> +2
	{"aff",   1, {T_REG}, 16, 2, 				"aff", 									1, 0},	--> +2


	{"and",   3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,	"et", 	1, 0},	--> +6
	{"add",   3, {T_REG, T_REG, T_REG}, 4, 10, 	"addition", 							1, 0},	--> +6
	{"sub",   3, {T_REG, T_REG, T_REG}, 5, 10, 	"soustraction", 						1, 0},	--> +6
	{"or",    3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6, 	"ou", 	1, 0},	--> +6
	{"xor",   3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6, 	"xou",	1, 0},	--> +6






	{"ldi",   3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,			"load index",	1, 1},		--> +4
	{"sti",   3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,			"store index", 	0, 1},		--> +4
	{"lldi",  3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,			"long load 	index",	1, 1},	--> +4
*/
