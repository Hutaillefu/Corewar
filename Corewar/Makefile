# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2019/01/09 16:36:19 by gzanarel     #+#   ##    ##    #+#        #
#    Updated: 2019/01/10 17:20:10 by gzanarel    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME = corewar

#NAME2 = asm

SRCS_C = srcs_cor/

#SRCS_A = srcs_asm/

S_C = $(SRCS_C)main.c $(SRCS_C)init.c $(SRCS_C)print.c

#S_A = fichier asm 

INC = include/

OBJ_C = $(addprefix ,$(S_C:.c=.o))

#OBJ_A = $(addprefix ,$(S_A:.c=.o))

LIB_DIR = ./libft
L_FT = $(LIB_DIR)
LIB_LNK = -L $(L_FT) -lft
LIB_INC	= -I $(L_FT)/libft.h

FLAGS = -Werror -Wextra -Wall

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ_C)
	@$(MAKE) -C libft/
	@gcc $(OBJ_C) -I $(INC) $(LIB_LNK) $(FLAGS) -o $(NAME)
	@echo "\n\033[32;01m./corewar.. done !\033[00m\n"

%.o:%.c $(INC)
	gcc -I $(INC) -c $< -o $@

clean:
	@rm -rf srcs/*.o
	@rm -rf $(L_FT)/objs/*.o
	@echo "\n\033[31;01mClean..\033[00m\n"

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(L_FT)/libft.a
	@echo "\n\033[31;01mFclean..\033[00m\n"

re: fclean all