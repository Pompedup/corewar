# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/03 18:57:57 by abezanni          #+#    #+#              #
#    Updated: 2018/06/29 14:57:31 by abezanni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OBJ =	$(OBJ_ALL)\
		$(OBJ1)\
		$(OBJ2)\

OBJ_ALL = $(SRC_ALL:.c=.o)

OBJ1 = $(SRC_1:.c=.o)

OBJ2 = $(SRC_2:.c=.o)


CC = @gcc

SRC =	$(SRC_ALL)\
		$(SRC_1)\
		$(SRC_2)\

SRC_NAME =	ft_lst.c\
			push.c\
			reverse_rotate.c\
			rotate.c\
			swap.c\
			ft_init.c\
			ft_errors.c\

SRC_NAME1 = checker.c\

SRC_NAME2 = push_swap.c\
			ft_search_best_move.c\
			ft_sort.c\
			ft_back_in_a.c\
			ft_recombined.c\
			ft_verif_sort.c\

SRC_ALL = $(addprefix src/,$(SRC_NAME))

SRC_1 = $(addprefix src/,$(SRC_NAME1))

SRC_2 = $(addprefix src/,$(SRC_NAME2))

NAME1 = asm

NAME2 = corewar

LIB_PATH = libft

LIB = libft/libft.a

INCLUDE = -I ./includes

CFLAGS = -Wall -Wextra -Werror $(INCLUDE)

all : libftcomp $(NAME1) $(NAME2)

$(NAME1) : $(LIB) $(OBJ1) $(OBJ_ALL)
	@gcc -o $(NAME1) $(CFLAGS) $(LIB) $(OBJ1) $(OBJ_ALL)
	@echo "\033[1;32mSucced checker\033[0m"

$(NAME2) : $(LIB) $(OBJ2) $(OBJ_ALL)
	@gcc -o $(NAME2) $(CFLAGS) $(LIB) $(OBJ2) $(OBJ_ALL)
	@echo "\033[1;32mSucced push_swap\033[0m"

$(OBJ_ALL) : includes/checker.h
$(OBJ1) : includes/checker.h
$(OBJ2) : includes/checker.h

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
