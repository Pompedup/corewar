# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pompedup <pompedup@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/03 18:57:57 by abezanni          #+#    #+#              #
#    Updated: 2018/09/01 17:40:16 by pompedup         ###   ########.fr        #
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

COMMON_FILES =

ASM_FILES =		asm.c\
				get_infos.c\
				get_lines.c\
				lines.c\

COREWAR_FILES =

COMMON_SRC =	$(addprefix src/,$(COMMON_FILES))

ASM_SRC = 		$(addprefix src/asm/,$(ASM_FILES))

COREWAR_SRC =	$(addprefix src/,$(COREWAR_FILES))

ASM_NAME = asm

COREWAR_NAME = corewar

LIB_PATH = libft

LIB = libft/libft.a

INCLUDE = -I ./inc

CFLAGS = -Wall -Wextra -Werror $(INCLUDE)

all : libftcomp $(ASM_NAME) test#$(COREWAR_NAME)

$(ASM_NAME) : $(LIB) $(ASM_OBJ) #$(COMMON_OBJ)
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
	@echo "\033[1;32mSucced clean of '*.o' from checker and push_swap\033[0m"

fclean : clean
	@/bin/rm -f $(LIB)
	@echo "\033[1;32mSucced clean of libft.a\033[0m"
	@/bin/rm -f $(NAME1) $(NAME2)
	@echo "\033[1;32mSucced clean checker and push_swap\033[0m"

re : fclean	all
	@echo "\033[1;32mSucced recompilation checker and push_swap\033[0m"
