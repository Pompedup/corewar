# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/03 18:57:57 by abezanni          #+#    #+#              #
#    Updated: 2018/10/31 17:42:21 by abezanni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY : all clean fclean re libftcomp

CC =			@gcc

FSANITIZE_FLAG = -g# -fsanitize=address

OBJ =			$(COMMON_OBJ)\
				$(ASM_OBJ)\
				$(COREWAR_OBJ)\

COMMON_OBJ =	$(COMMON_SRC:.c=.o)

ASM_OBJ =		$(ASM_SRC:.c=.o)

COREWAR_OBJ =	$(COREWAR_SRC:.c=.o)

SRC =			$(COMMON_SRC)\
				$(ASM_SRC)\
				$(COREWAR_SRC)\

COMMON_FILES =	global.c\

ASM_STRUCT =	t_arg.c\
				t_elem.c\
				t_file.c\
				t_function.c\

ASM_GET_DATA =	check_label.c\
				get_arg.c\
				get_elem.c\
				get_functions.c\
				get_infos.c\
				get_label.c\
				get_pos.c\
				get_string.c\
				get_type.c\
				last_verifications.c\

ASM_WRITE =		write.c\

ASM_VERIF =		error_type.c\
				verif_elem_str.c\
				verif_file_name.c\

ASM_FILES =		asm.c\
				step.c\
				help_error.c\
				handle_args.c\
				$(addprefix get_data/,$(ASM_GET_DATA))\
				$(addprefix struct/,$(ASM_STRUCT))\
				$(addprefix write/,$(ASM_WRITE))\
				$(addprefix verif/,$(ASM_VERIF))\

COREWAR_FILES =	corewar.c\
				execute_the_battle.c\
				get_arguments.c\
				get_instructions.c\
				get_values.c\
				handle_processus.c\
				init_corewar.c\
				instructions/ft_add.c\
				instructions/ft_aff.c\
				instructions/ft_and.c\
				instructions/ft_fork.c\
				instructions/ft_ld.c\
				instructions/ft_ldi.c\
				instructions/ft_lfork.c\
				instructions/ft_live.c\
				instructions/ft_lld.c\
				instructions/ft_lldi.c\
				instructions/ft_or.c\
				instructions/ft_st.c\
				instructions/ft_sti.c\
				instructions/ft_sub.c\
				instructions/ft_xor.c\
				instructions/ft_zjump.c\
				manage_error.c\
				number_players.c\
				parse_argv.c\
				players_charged.c\
				read_file_players.c\
				create_players.c\
				print_core.c\
				free_corewar.c\
				viz.c\
				details_viz.c\

COMMON_SRC =	$(addprefix src/common/,$(COMMON_FILES))

ASM_SRC =		$(addprefix src/asm/,$(ASM_FILES))

COREWAR_SRC =	$(addprefix src/corewar/,$(COREWAR_FILES))

ASM_NAME =		asm
ASM_NAME_DEBUG =		asm_debug

NAME = $(ASM_NAME) $(COREWAR_NAME)

COREWAR_NAME =	corewar
COREWAR_NAME_DEBUG =	corewar_debug

LIB_PATH =		libft

LIB =			libft/libft.a

INCLUDE =		-I ./inc

CFLAGS = -Wall -Wextra -Werror $(INCLUDE)

.PHONY = libftcomp

ERROR_FILE =	$(addprefix error_champ/arg/, $(ERROR_ARG))\
				$(addprefix error_champ/comment/, $(ERROR_COMMENT))\
				$(addprefix error_champ/dir/, $(ERROR_DIR))\
				$(addprefix error_champ/name/, $(ERROR_NAME))\
				$(addprefix error_champ/reg/, $(ERROR_REG))\

ERROR_ARG =		miss_sep.s\
				too_much.s\
				miss_arg_between.s\

ERROR_COMMENT =	char_after_comment.s\
				comment_too_long.s\
				second_comment.s\

ERROR_DIR =		dir_without_value.s\
				dir_wrong_value.s\

ERROR_NAME =	char_after_name.s\
				name_too_long.s\
				second_name.s\

ERROR_REG =		reg_without_int.s\

all : libftcomp $(NAME)

$(COREWAR_NAME) : $(LIB) $(COREWAR_OBJ) $(COMMON_OBJ)
	$(CC) -o $(COREWAR_NAME) $(CFLAGS) $(LIB) $(COREWAR_OBJ) $(COMMON_OBJ)
	@echo "\033[1;32mSucced corewar\033[0m"

$(ASM_NAME) : $(LIB) $(ASM_OBJ) $(COMMON_OBJ)
	$(CC) -o $(ASM_NAME) $(CFLAGS) $(LIB) $(ASM_OBJ) $(COMMON_OBJ)
	@echo "\033[1;32mSucced asm\033[0m"


$(ASM_NAME_DEBUG) : $(LIB) $(ASM_OBJ) $(COMMON_OBJ)
	$(CC) $(CFLAGS) $(FSANITIZE_FLAG) -o $(ASM_NAME) $(LIB) $(ASM_OBJ) $(COMMON_OBJ)
	@echo "\033[1;32mSucced asm with $(FSANITIZE_FLAG)\033[0m"

$(COREWAR_NAME_DEBUG) : $(LIB) $(COREWAR_OBJ) $(COMMON_OBJ)
	$(CC) $(CFLAGS) $(FSANITIZE_FLAG) -o $(COREWAR_NAME) $(LIB) $(COREWAR_OBJ) $(COMMON_OBJ)
	@echo "\033[1;32mSucced corewar with $(FSANITIZE_FLAG)\033[0m"

DEBUG : libftcomp $(ASM_NAME_DEBUG) $(COREWAR_NAME_DEBUG)

$(COMMON_OBJ) : inc/common.h
$(ASM_OBJ) : inc/asm.h inc/common.h inc/asm_struct_define.h
$(COREWAR_OBJ) : inc/corewar.h inc/common.h

test : print_memory.c
	$(CC) print_memory.c $(LIB) -o memory

libftcomp :
	@make -C $(LIB_PATH)

clean :
	@make clean -C $(LIB_PATH)
	@/bin/rm -f $(OBJ)
	@echo "\033[1;32mSucced clean of '*.o' from asm and corewar\033[0m"

fclean : clean
	@/bin/rm -f $(LIB)
	@echo "\033[1;32mSucced clean of libft.a\033[0m"
	@/bin/rm -f $(ASM_NAME) $(COREWAR_NAME) memory #remove memory
	@echo "\033[1;32mSucced clean asm and corewar\033[0m"

re : fclean	all
	@echo "\033[1;32mSucced recompilation asm and corewar\033[0m"

del_cor:
	@/bin/rm -f ****.cor

errors: $(ERROR_FILE)
	./$(ASM_NAME) $^
