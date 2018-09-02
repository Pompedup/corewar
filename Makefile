# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/03 18:57:57 by abezanni          #+#    #+#              #
#    Updated: 2018/09/02 15:32:20 by ccoupez          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC =			@gcc

OBJ =			$(COMMON_OBJ)\
				$(ASM_OBJ)\
				$(VM_OBJ)\

COMMON_OBJ =	$(COMMON_SRC:.c=.o)

ASM_OBJ =		$(ASM_SRC:.c=.o)

VM_OBJ =	$(VM_SRC:.c=.o)

SRC =			$(COMMON_SRC)\
				$(ASM_SRC)\
				$(VM_SRC)\

COMMON_FILES =

ASM_FILES =		asm.c\
				get_infos.c\
				get_lines.c\
				lines.c\

VM_FILES =		charge_players_in_core.c\
				execute_the_battle.c\
				handle_processus.c\
				init_vm.c\
				manage_error.c\
				number_players.c\
				parse_argv.c\
				read_file_players.c\
				register_players.c\
				vm.c\

COMMON_SRC =	$(addprefix src/,$(COMMON_FILES))

ASM_SRC = 		$(addprefix src/asm/,$(ASM_FILES))

VM_SRC =	$(addprefix src/vm/,$(VM_FILES))

ASM_NAME = asm

VM_NAME = vm

LIB_PATH = libft

LIB = libft/libft.a

INCLUDE = -I ./inc

CFLAGS = -Wall -Wextra -Werror $(INCLUDE)

all : libftcomp $(VM_NAME) #$(ASM_NAME) #test

$(ASM_NAME) : $(LIB) $(ASM_OBJ) #$(COMMON_OBJ)
	$(CC) -o $(ASM_NAME) $(CFLAGS) $(LIB) $(ASM_OBJ) $(COMMON_OBJ)
	@echo "\033[1;32mSucced asm\033[0m"

$(VM_NAME) : $(LIB) $(VM_OBJ) $(COMMON_OBJ)
	$(CC) -o $(VM_NAME) $(CFLAGS) $(LIB) $(VM_OBJ) $(COMMON_OBJ)
	@echo "\033[1;32mSucced vm\033[0m"

$(COMMON_OBJ) : inc/common.h
$(ASM_OBJ) : inc/asm.h inc/common.h
$(VM_OBJ) : inc/vm.h inc/common.h

test : print_memory.c
	$(CC) print_memory.c $(LIB) -o memory

libftcomp :
	@make -C $(LIB_PATH)

clean :
	@make clean -C $(LIB_PATH)
	@/bin/rm -f $(OBJ)
	@echo "\033[1;32mSucced clean of '*.o' from asm and vm\033[0m"

fclean : clean
	@/bin/rm -f $(LIB)
	@echo "\033[1;32mSucced clean of libft.a\033[0m"
	@/bin/rm -f $(NAME1) $(NAME2)
	@echo "\033[1;32mSucced clean asm and vm\033[0m"

re : fclean	all
	@echo "\033[1;32mSucced recompilation asm and vm\033[0m"
