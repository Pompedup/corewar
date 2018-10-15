/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 09:44:42 by ccoupez           #+#    #+#             */
/*   Updated: 2018/10/12 16:59:35 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "common.h"

#define CYCLE_DEBUG			800

# define SHORT				32768
# define UNSIGNED_CHAR		128
# define USAGE 				USAGE1 USAGE2
# define USAGE1				"Usage: ./corewar [-dump nbr_cycles]"
# define USAGE2				"[[-n number] champion1.cor] ..."
# define ERR_MESS_00		"incorrect defines"
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
# define ERR_MESS_11		" has too large a code"
# define ERR_MESS_12		"cannot read comment from file "
# define ERR_MESS_13		"cannot read the program of file "
# define ERR_MESS_14		"difference between progam size expected and read"
# define ERR_MESS_15		"too many players"
# define ERR_MESS_16		"at least one player is needed"
# define ERR_MESS_17		"argument for number of player is not an int"
# define ERR_MESS_18		"a player cannot have a number already given or 0"
# define FAIL_MEMALLOC_0	"ft_memalloc of vm->info failed"
# define FAIL_MEMALLOC_1	"ft_memalloc of vm->info->player failed"
# define FAIL_MEMALLOC_2	"ft_memalloc of vm->info->player->header failed"
# define FAIL_MEMALLOC_3	"ft_memalloc of vm->info->process failed"
# define FAIL_MEMALLOC_4	"ft_memalloc of new_color failed"
# define FAIL_MEMALLOC_5	"ft_memalloc of values failed"

//ORDONNE DANS LE SENS COULEUR CLASSIQUE / SURBRILLANCE (derniere instruction en date) / SURLIGNEMENT PC
#define TAB_COLOR	{GREEN, PINK, BLUE, ORANGE, GREEN_S, PINK_S, BLUE_S, ORANGE_S, GREEN_PC, PINK_PC, BLUE_PC, ORANGE_PC, GREY_PC, GREY}
#define GREEN				0x00ff00
#define PINK				0xff0000
#define BLUE				0x0000ff
#define ORANGE				0xf0f0f0
//////////
#define GREEN_S				0xcdefb2
#define PINK_S				0xff0099
#define BLUE_S				0xcfebfd
#define ORANGE_S			0xfdc085
//////////
#define GREEN_PC			0xace580
#define PINK_PC				0xffb6c1
#define BLUE_PC				0x9fd7fb
#define ORANGE_PC			0xfd9735
//////////
#define GREY_PC				0x808080
#define GREY				0xdfdfdf
//////////
// #define GREEN_LIFE			0x00ff00
// #define PINK_LIFE			0xff0000
// #define BLUE_LIFE			0x0000ff
// #define ORANGE_LIFE			0xf0f0f0

/*
********************************************************************************
**	s_player contains
**	- number of player (either from 1 to MAX_PLAYER or set through option -n)
**	- name_file from the file that detailed the champion
**	- color (as defined by the order set in TAB_COLOR with number of player)
**	- header refers to the structure defined in common.h
**	- process (the array of char with the entire champion used to fill vm->core)
**	- len_process (the lenght of the player process)
**	- next that points to the next player
********************************************************************************
*/

typedef struct			s_player
{
	int					num;//num joueur faut peut etre le mettre dans le r1
	char				*name_file;
	int					color;
	header_t			*header;
	char				process[CHAMP_MAX_SIZE + 1];
	int					len_process;
	struct s_player		*next;
}						t_player;

/*
********************************************************************************
**	s_process contains
**	- name of program
**	- color
**	-
**	-
**	-
**	-
**	-
********************************************************************************
*/

typedef struct			s_process
{
	char				name[PROG_NAME_LENGTH + 1];
	int					color;
	int					reg[REG_NUMBER];//de REG_SIZE un int 4 octets
	int					pc;
	int					pc_tmp;
	int					carry;
	int					live;
	int					type_instruc[2];
	int					args[3];
	int					color_live;
	int					nb_cycle_instruc;
	struct s_process	*next;
}						t_process;

/*
********************************************************************************
** structure pour gerer la liste chainée des players
********************************************************************************
*/

typedef struct			s_info
{
	int					nb_players;
	t_player			*first_player;
	t_process			*first_processus;
}						t_info;

/*
********************************************************************************
**	t_corevm
**	- core[MEM_SIZE] represents the actual vm (an array of char)
**	- dump will be the nbr of cycles after which core will be printed on the
**		standard output
**	- nb_cycle
**	-
********************************************************************************
*/

typedef struct			s_corevm
{
	char				**argv; //pour le parsing
	int					viz; //option visu librairie possible : OpenGL, SDL, nCurses, ... (bonus)
	t_info				*info; // pointeur vers la structure qui gere la liste des players

	//ici plus pour la battle
	char				core[MEM_SIZE];
	unsigned int		color[MEM_SIZE];
	int					dump;//unsigned int

	int					nbr_total_cycles;

	int					cycle_to_die;
	
	int					octet_line_viz;
	int					nb_lives;
}						t_corevm;

typedef struct			s_ptr_func
{
	void				(*ptrfunc) (t_corevm *core, t_process *actual);
	int					code_instruction;
}						t_ptr_func;

extern t_ptr_func	g_instruc_func[];

/*
********************************************************************************
**						INIT_VM_C									 		  **
********************************************************************************
*/

void					init_vm(char **av, t_corevm *vm);

/*
********************************************************************************
**						PARSE_ARGV_C								 		  **
********************************************************************************
*/

void   					parse_argv(t_corevm *vm);

/*
********************************************************************************
**						REGISTER_PLAYERS_C							 		  **
********************************************************************************
*/

void					create_player(t_corevm *vm, int num,  int index);

/*
********************************************************************************
**						READ_FILE_PLAYER_C							 		  **
********************************************************************************
*/

void					read_magic(t_player *player, t_corevm *vm, int fd);
void					read_name(t_player *player, t_corevm *vm, int fd);
void					read_prog_size(t_player *player, t_corevm *vm, int fd);
void					read_comment(t_player *player, t_corevm *vm, int fd);
void					read_programme(t_player *player, t_corevm *vm, int fd);

/*
********************************************************************************
**						NUMBER_PLAYERS_C							 		  **
********************************************************************************
*/

void    				number_players(t_corevm *vm);
int						unused_num(t_corevm *vm, int num);

/*
********************************************************************************
**						PLAYERS_CHARGED								 	 	 **
********************************************************************************
*/

void					players_charged_in_core(t_corevm *vm);

/*
********************************************************************************
**						MANAGE_ERROR_C									 	  **
********************************************************************************
*/

void    				ft_error(t_corevm *vm, char *mess_error, int to_free);
void					ft_read_error(t_corevm *vm, char *mess_error, int fd);
void					ft_dump_exit(t_corevm *vm);

/*
********************************************************************************
**						PRINT_MEMORY_C									 	  **
********************************************************************************
*/

int						print_player(char *av, int i);
void					print_memory(const void *addr, size_t size);

/*
********************************************************************************
**						HANDLE_PROCESSUS_C						     		  **
********************************************************************************
*/

t_process				*create_process(t_corevm *vm, int pc, t_player *player);
void					put_process_front(t_process **first, \
						t_process *process);

/*
********************************************************************************
**						EXECUTE_THE_BATTLE_C						     	  **
********************************************************************************
*/

void					execute_the_battle(t_corevm *vm);
void					pc_color(t_corevm *vm, t_process *process);

/*
********************************************************************************
**						GET_INSTRUCTIONS_C					     		  	  **
********************************************************************************
*/

void					manage_instruction(t_corevm *vm, t_process *process);
void					get_instruction_type(t_corevm *vm, t_process *process);
void					execute_instruction(t_corevm *vm, t_process *process);
void					move_pc(t_process *process, t_op g_tab);
void					get_pc_tmp(t_process *process, t_op g_tab);

/*
********************************************************************************
**						GET_ARGUMENTS_C			     						  **
********************************************************************************
*/

void					get_one_octet(t_corevm *vm, t_process *process, int i);
void					get_two_octets(t_corevm *vm, t_process *process, int i);
void					get_four_octets(t_corevm *vm, t_process *process,\
						int i);
int						*get_values(t_corevm *vm, t_process *process,\
						char num_arg, int l);
t_bool					test_args(t_process *process, t_op g_tab);
void					get_args(t_corevm *vm, t_process *process, t_op g_tab);
/*
********************************************************************************
**						INSTRUCTIONS/				     				 	  **
********************************************************************************
*/

void						ft_live(t_corevm *vm, t_process *process);
void						ft_ld(t_corevm *vm, t_process *process);
void	    				ft_st(t_corevm *vm, t_process *process);
void						ft_add(t_corevm *vm, t_process *process);
void	    				ft_sub(t_corevm *vm, t_process *process);
void						ft_and(t_corevm *vm, t_process *process);
void	    				ft_or(t_corevm *vm, t_process *process);
void	    				ft_xor(t_corevm *vm, t_process *process);
void						ft_zjmp(t_corevm *vm, t_process *process);
void						ft_ldi(t_corevm *vm, t_process *process);
void	    				ft_sti(t_corevm *vm, t_process *process);
void						ft_fork(t_corevm *vm, t_process *process);
void	    				ft_lld(t_corevm *vm, t_process *process);
void	    				ft_lldi(t_corevm *vm, t_process *process);
void	    				ft_lfork(t_corevm *vm, t_process *process);
void						ft_aff(t_corevm *vm, t_process *process);

/*
********************************************************************************
**						PRINT_CORE_C					     			 	  **
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
