/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 09:44:42 by ccoupez           #+#    #+#             */
/*   Updated: 2018/07/17 16:31:25 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include <fcntl.h>
#include <stdio.h>

# define LIVE   1
# define LD		2
# define ST		3
# define ADD	4
# define SUB	5
# define AND	6
# define OR		7
# define ZJMP	9
# define XOR	8
# define LDI	10
# define STI	11
# define FORK	12
# define LLD	13
# define LLDI	14
# define LFORK	15
# define AFF	16
# define TOTAL_SIZE (CHAMP_MAX_SIZE + PROG_NAME_LENGTH + COMMENT_LENGTH + 1)

typedef struct		s_players
{
	char			name[PROG_NAME_LENGTH + 1];
	char			comment[COMMENT_LENGTH + 1];
	int				num; // numero du joueur (choisi ou donnee automatiquement)
	int				color;
	char			*file;// on recup tt le fichier avec read
}					t_players;

typedef struct		s_corevm
{
	char			**argv;
	char			core[MEM_SIZE];
	t_players		*players[MAX_PLAYERS + 1];
	int				nb_cycles;
	int				nb_players;
	int				dump;
	int				visu;	
}					t_corevm;

typedef struct		s_instruction
{
	char			code_instruction;
	int				param[4];
}					t_instruction;

typedef struct		s_func
{
	char			*(*ptrfunc) (t_corevm *core, t_players *players,
					t_instruction instruction);
	int				code_instruction;
}					t_func;	

/*
** vm.c
*/

void					init_vm(char **av, t_corevm *vm);

/*
** parse_argv.c
*/

void   				parse_argv(t_corevm *vm);

/*
** print_memory.c
*/

int					print_player(char *av, int i);

/*
** manage_error.c
*/

void     ft_error(t_corevm *vm,  int num_error);

/*
** all instructionss
*/

int     ft_live(t_corevm *core, t_players *players, t_instruction instruction);
int		ft_ld(t_corevm *core, t_players *players, t_instruction instruction);
int     ft_st(t_corevm *core, t_players *players, t_instruction instruction);
int		ft_add(t_corevm *core, t_players *players, t_instruction instruction);
int     ft_sub(t_corevm *core, t_players *players, t_instruction instruction);
int		ft_and(t_corevm *core, t_players *players, t_instruction instruction);
int     ft_or(t_corevm *core, t_players *players, t_instruction instruction);
int     ft_xor(t_corevm *core, t_players *players, t_instruction instruction);
int		ft_zjump(t_corevm *core, t_players *players, t_instruction instruction);
int		ft_ldi(t_corevm *core, t_players *players, t_instruction instruction);
int     ft_sti(t_corevm *core, t_players *players, t_instruction instruction);
int		ft_fork(t_corevm *core, t_players *players, t_instruction instruction);
int     ft_lld(t_corevm *core, t_players *players, t_instruction instruction);
int     ft_lldi(t_corevm *core, t_players *players, t_instruction instruction);
int     ft_lfork(t_corevm *core, t_players *players, t_instruction instruction);
int		ft_aff(t_corevm *core, t_players *players, t_instruction instruction);

//Trois méthodes d’adressage de la mémoire sont possibles 
//dans une instruction :
//Relatif : C’est le mode par défaut. Il est relatif à la 
//case de l’instruction en cours d’exécution. Par exemple, 
//3 pointe vers la troisième case après la case de 
//l’instruction en cours d’exécution.

//Indirect : Est indiqué par un signe @. 
//L’adresse après le signe @ n’est pas l’adresse pointée 
//mais l’adresse de l’adresse pointée. 
//Par exemple @3 pointe vers la case dont l’adresse est 3 cases 
//après celle de l’instruction en cours. Attention, la case 
//contenant l’adresse doit être du type DAT (cf plus loin) 
//sans quoi, le programme s’arrête sur une erreur d’indirection.

//Immédiat : Est indiqué par un signe # avant 
//l’argument. Indique une valeur numérique, sans référence 
//d’adresse. Donc #3 est la valeur numérique 3.