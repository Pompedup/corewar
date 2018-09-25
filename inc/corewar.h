/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecesari <ecesari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 09:44:42 by ccoupez           #+#    #+#             */
/*   Updated: 2018/09/25 19:10:45 by ecesari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "common.h"
# include <stdio.h>// Asupprimer

# define USAGE "Usage: ./corewar [-dump nbr_cycles] [[-n number] champion1.cor] ..."
# define ERR_MESS_0			"not enough arguments.\n" USAGE
# define ERR_MESS_1			"incorrect arguments.\n" USAGE
# define ERR_MESS_2			"argument for dump is not an unsigned int"
# define ERR_MESS_3			"argument for dump must be superior to 0"
# define ERR_MESS_4			"incorrect name of the champion file"
# define ERR_MESS_5			"cannot open file "
# define ERR_MESS_6			"cannot close file "
# define ERR_MESS_7			"incorrect magic number"
# define ERR_MESS_8			"cannot read magic number from file "
# define ERR_MESS_9			"cannot read name of player from file "
# define ERR_MESS_10		"cannot read the size of the program of file "
# define ERR_MESS_11		"champion is too large"
# define ERR_MESS_12		"cannot read comment from file "
# define ERR_MESS_13		"cannot read the program of file "
# define ERR_MESS_14		"difference between progam size expected and the one read"
# define ERR_MESS_15		"too many players"
# define ERR_MESS_16		"at least one player is needed"
# define ERR_MESS_17		"argument for number of player is not an int"
# define ERR_MESS_18		"a player cannot have number 0 or a number already given"
# define FAIL_MEMALLOC_0	"ft_memalloc of vm->info failed.\n" USAGE
# define FAIL_MEMALLOC_1	"ft_memalloc of player failed.\n" USAGE
# define FAIL_MEMALLOC_2	"ft_memalloc of header failed.\n" USAGE
# define FAIL_MEMALLOC_3	"ft_memalloc of process failed.\n" USAGE


typedef struct			s_player
{
	int					num; // num joueur a voir faut peut etre le mettre dans le r1
	char				*name_file;
	int					color;
	header_t			*header;
	char				process[CHAMP_MAX_SIZE + 1];
	int					len_process;
	struct s_player		*next;
}						t_player;

typedef struct			s_process
{
	char				name[PROG_NAME_LENGTH + 1];
	int					color;
	int					reg[REG_NUMBER]; // de REG_SIZE #define REG_SIZE	4 un int 4 octets
	int					pc; //programme counter
	int					carry; //une retenu des instructions ou ya des calculs (si jai bien compris!?)
	int					alive; //pour voir la derniere foi qu'il a dit quil etait en vie

	int					type_instruc[2];
	int					args[3];
	int					nb_cycle_instruc;
	struct s_process	*next;
}						t_process;

typedef struct			s_info //structure pour gerer la liste chainée des players
{
	int					nb_players;
	t_player			*first_player;
	t_process			*first_processus;
}						t_info;

typedef struct			s_corevm
{
	char				**argv; //pour le parsing
	int					visu; //option visu librairie possible : OpenGL, SDL, nCurses, ... (bonus)
	t_info				*info; // pointeur vers la structure qui gere la liste des players

	//ici plus pour la battle
	char				core[MEM_SIZE];
	int					dump;//unsigned int
	int					nb_cycle;
	int					cycle_to_die;
	int					nb_lives; //associer au define NBR_LIVE. Si au cours d’une de ces vérifications on se rend compte qu’il y a eu au moins NBR_LIVE exécutions de live depuis la dernière vérification en date, on décrémente CYCLE_TO_DIE de CYCLE_DELTA unités
	int					nb_max_live; //define NBR_LIVE
}						t_corevm;

typedef struct			s_ptr_func
{
	void				(*ptrfunc) (t_corevm *core, t_process *actual);
	int					code_instruction;
}						t_ptr_func;

extern t_ptr_func	g_instruc_func[];

/*
********************************************************************************
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
**						    _PLAYERS_CHARGEDC							 	  **
********************************************************************************
*/

void					players_charged_in_core(t_corevm *vm);

/*
********************************************************************************
**						      MANAGE_ERROR_C							 	  **
********************************************************************************
*/

void    				ft_error(t_corevm *vm, char *mess_error, int to_free);
void					ft_read_error(t_corevm *vm, char *mess_error, int fd);
void					ft_dump_exit(t_corevm *vm);

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

t_process				*create_process(t_corevm *vm, int pc, t_player *player);
void					put_process_front(t_process **first, t_process *process);

/*
********************************************************************************
**						      EXECUTE_THE_BATTLE_C				     		  **
********************************************************************************
*/

void					execute_the_battle(t_corevm *vm);

/*
********************************************************************************
**						      CHECKING_BATTLE_C					     		  **
********************************************************************************
*/

void					check_if_process_lives(t_process *process);
void					check_nb_lives(t_corevm *vm);
void					check_dump(t_corevm *vm);
int						check_max_checks(t_corevm *vm, int tmp_cycle);

/*
********************************************************************************
**						      GET_INSTRUCTIONS_C			     			  **
********************************************************************************
*/

void					manage_instruction(t_corevm *vm, t_process *process);
void					get_instruction_type(t_corevm *vm, t_process *actual);
void					execute_instruction(t_corevm *vm, t_process *actual);


/*
********************************************************************************
**						      GET_ARGUMENTS_C			     				  **
********************************************************************************
*/

void					get_one_octet(t_corevm *vm, t_process *process, int i);
void					get_two_octets(t_corevm *vm, t_process *process, int i);
void					get_four_octets(t_corevm *vm, t_process *process, int i);
int						*get_values(t_corevm *vm, t_process *process, char num_arg);
t_bool					test_args(t_process *process, t_op g_tab);
void					get_args(t_corevm *vm, t_process *process, t_op g_tab);
/*
********************************************************************************
**						      INSTRUCTIONS/				     			 	  **
********************************************************************************
*/

void					ft_live(t_corevm *vm, t_process *process);
void					ft_ld(t_corevm *vm, t_process *process);
void    				ft_st(t_corevm *vm, t_process *process);
void					ft_add(t_corevm *vm, t_process *process);
void    				ft_sub(t_corevm *vm, t_process *process);
void					ft_and(t_corevm *vm, t_process *process);
void    				ft_or(t_corevm *vm, t_process *process);
void    				ft_xor(t_corevm *vm, t_process *process);
void					ft_zjmp(t_corevm *vm, t_process *process);
void					ft_ldi(t_corevm *vm, t_process *process);
void    				ft_sti(t_corevm *vm, t_process *process);
void					ft_fork(t_corevm *vm, t_process *process);
void    				ft_lld(t_corevm *vm, t_process *process);
void    				ft_lldi(t_corevm *vm, t_process *process);
void    				ft_lfork(t_corevm *vm, t_process *process);
void					ft_aff(t_corevm *vm, t_process *process);

/*
********************************************************************************
**						      PRINT_CORE_C				     			 	  **
********************************************************************************
*/

void					print_core(t_corevm *vm);


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
