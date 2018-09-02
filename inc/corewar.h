/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 09:44:42 by ccoupez           #+#    #+#             */
/*   Updated: 2018/09/02 18:50:08 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "common.h"
# include <stdio.h>// Asupprimer

# define LIVE   		0x01
# define LD				0x02
# define ST				0x03
# define ADD			0x04
# define SUB			0x05
# define AND			0x06
# define OR				0x07
# define XOR			0x08
# define ZJMP			0x09
# define LDI			0x0a
# define STI			0x0b
# define FORK			0x0c
# define LLD			0x0d
# define LLDI			0x0e
# define LFORK			0x0f
# define AFF			0x10

typedef struct			s_player
{
	int					num; // num joueur a voir faut peut etre le mettre dans le r1
	char				*name_file; //a supprimer cest juste pr afficher pendant le parsing
	int					color;
	header_t			*header;
	char				process[CHAMP_MAX_SIZE + 1];
	int					len_process;
	struct s_player		*next;
}						t_player;

typedef struct			s_process
{
	int					color;
	int					reg[REG_NUMBER]; // de REG_SIZE #define REG_SIZE	4 un int 4 octets
	int					pc; //programme counter
	int					carry; //une retenu des instructions ou ya des calculs (si jai bien compris!?)
	int					nb_cycle;
	//int				last_live; pour voir la derniere foi qu'il a dit quil etait en vie
	struct s_process	*next;
}						t_process;

typedef struct			s_info_players //structure pour gerer la liste chainée des players
{
	int					nb_players;
	t_player			*first_player;
	t_process			*first_processus;
}						t_info_players;

typedef struct			s_corevm
{
	char				**argv; //pour le parsing
	int					visu; //option visu librairie possible : OpenGL, SDL, nCurses, ... (bonus)
	t_info_players		*info_players; // pointeur vers la structure qui gere la liste des players

	//ici plus pour la battle
	char				core[MEM_SIZE]; //larene
	int					nb_total_cycles; //associer au define CYCLE_TO_DIE qui est le max && Si on n’a pas décrémenté CYCLE_TO_DIE depuis MAX_CHECKS vérifications, on le décrémente
	int					cycle_to_die; // = CYCLE_TO_DIE ->se decrement quand :
						//Si on n’a pas décrémenté CYCLE_TO_DIE depuis MAX_CHECKS vérifications,on le décrémente.
	int					nb_check;	 //??? voir ci dessus
	int					dump; //je sais pas trop encore
	int					nb_live; //associer au define NBR_LIVE. Si au cours d’une de ces vérifications on se rend compte qu’il y a eu au moins NBR_LIVE exécutions de live depuis la dernière vérification en date, on décrémente CYCLE_TO_DIE de CYCLE_DELTA unités
}						t_corevm;

/*
** structure pour faire un tableau de pointeur sur fonction
** et appeler les instructions comme dans printf (avec le code d'instruction)
*/

typedef struct			s_ptr_func
{
	char				*(*ptrfunc) (t_corevm *core, t_player *player);
	int					code_instruction;
}						t_ptr_func;
/*
******************************************************************************** #ecesari
**								INIT_VM_C								 	  **
********************************************************************************
*/

void					init_vm(char **av, t_corevm *vm);

/*
********************************************************************************
**						     PARSE_ARGV_C								 	  **
********************************************************************************
*/

void   					parse_argv(t_corevm *vm);

/*
********************************************************************************
**						   REGISTER_PLAYERS_C							 	  **
********************************************************************************
*/

void					create_player(t_corevm *vm, int num,  int index);

/*
********************************************************************************
**						     READ_FILE_PLAYER_C							 	  **
********************************************************************************
*/

void					read_magic(t_player *player, t_corevm *vm, int fd);
void					read_name(t_player *player, t_corevm *vm, int fd);
void					read_prog_size(t_player *player, t_corevm *vm, int fd);
void					read_comment(t_player *player, t_corevm *vm, int fd);
void					read_programme(t_player *player, t_corevm *vm, int fd);

/*
********************************************************************************
**						    NUMBER_PLAYERS_C							 	  **
********************************************************************************
*/

void    				number_players(t_corevm *vm);
int						unused_num(t_corevm *vm, int num);

/*
********************************************************************************
**						    CHARGE_PLAYERS_C							 	  **
********************************************************************************
*/

void					charge_players_in_core(t_corevm *vm);

/*
********************************************************************************
**						      MANAGE_ERROR_C							 	  **
********************************************************************************
*/

void    				 ft_error(t_corevm *vm,  int num_error);
void					ft_read_error(t_corevm *vm, int num_error, int fd);

/*
********************************************************************************
**						      PRINT_MEMORY_C							 	  **
********************************************************************************
*/

int						print_player(char *av, int i);
void					print_memory(const void *addr, size_t size);

/*
********************************************************************************
**						      HANDLE_PROCESSUS_C				     		  **
********************************************************************************
*/

t_process				*create_process(t_corevm *vm, int pc, int num, unsigned int color);
void					put_process_front(t_process **first, t_process *process);

/*
********************************************************************************
**						      INSTRUCTIONS				     			 	  **
********************************************************************************
*/

/*int						ft_live(t_corevm *core, t_player *player);
int						ft_ld(t_corevm *core, t_player *player);
int     				ft_st(t_corevm *core, t_player *player);
int						ft_add(t_corevm *core, t_player *player);
int     				ft_sub(t_corevm *core, t_player *player);
int						ft_and(t_corevm *core, t_player *player);
int     				ft_or(t_corevm *core, t_player *player);
int     				ft_xor(t_corevm *core, t_player *player);
int						ft_zjump(t_corevm *core, t_player *player);
int						ft_ldi(t_corevm *core, t_player *player);
int     				ft_sti(t_corevm *core, t_player *player);
int						ft_fork(t_corevm *core, t_player *player);
int     				ft_lld(t_corevm *core, t_player *player);
int     				ft_lldi(t_corevm *core, t_player *player);
int     				ft_lfork(t_corevm *core, t_player *player);
int						ft_aff(t_corevm *core, t_player *player);*/






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

#endif
