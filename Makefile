# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/03 18:57:57 by abezanni          #+#    #+#              #
#    Updated: 2018/10/06 18:01:36 by abezanni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC =			@gcc

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

ASM_GET_DATA =	get_dir.c\
				get_elem.c\
				get_function.c\
				get_ind.c\
				get_infos.c\
				get_label.c\
				get_reg.c\
				get_string.c\
				last_verifications.c\

ASM_WRITE =		write.c\

ASM_FILES =		asm.c\
				step.c\
				$(addprefix get_data/,$(ASM_GET_DATA))\
				$(addprefix struct/,$(ASM_STRUCT))\
				$(addprefix write/,$(ASM_WRITE))\

COREWAR_FILES =	charge_players_in_core.c\
				execute_the_battle.c\
				handle_processus.c\
				init_corewar.c\
				manage_error.c\
				number_players.c\
				parse_argv.c\
				read_file_players.c\
				register_players.c\
				corewar.c\

COMMON_SRC =	$(addprefix src/common/,$(COMMON_FILES))

ASM_SRC =		$(addprefix src/asm/,$(ASM_FILES))

COREWAR_SRC =	$(addprefix src/corewar/,$(COREWAR_FILES))

ASM_NAME =		asm

NAME = $(ASM_NAME) $(COREWAR_NAME)

COREWAR_NAME =	corewar

LIB_PATH =		libft

LIB =			libft/libft.a

INCLUDE =		-I ./inc

CFLAGS = -Wall -Wextra -Werror $(INCLUDE)

.PHONY = libftcomp

all : libftcomp $(NAME)

$(ASM_NAME) : $(LIB) $(ASM_OBJ) $(COMMON_OBJ)
	$(CC) -o $(ASM_NAME) $(CFLAGS) $(LIB) $(ASM_OBJ) $(COMMON_OBJ)
	@echo "\033[1;32mSucced asm\033[0m"

$(COREWAR_NAME) : $(LIB) $(COREWAR_OBJ) $(COMMON_OBJ)
	$(CC) -o $(COREWAR_NAME) $(CFLAGS) $(LIB) $(COREWAR_OBJ) $(COMMON_OBJ)
	@echo "\033[1;32mSucced corewar\033[0m"

$(COMMON_OBJ) : inc/common.h
$(ASM_OBJ) : inc/asm.h inc/common.h
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
