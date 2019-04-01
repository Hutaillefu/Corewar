# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2019/01/09 16:36:19 by gzanarel     #+#   ##    ##    #+#        #
#    Updated: 2019/03/22 20:43:44 by gzanarel    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME = corewar

SRCS_C = srcs_cor/

S_C = $(SRCS_C)main.c $(SRCS_C)init.c $(SRCS_C)print.c $(SRCS_C)parse.c \
	$(SRCS_C)cycle.c $(SRCS_C)error.c $(SRCS_C)read_infos.c $(SRCS_C)op.c \
	$(SRCS_C)parse_instruct.c $(SRCS_C)processus.c $(SRCS_C)tools_instruct.c \
	$(SRCS_C)flags.c $(SRCS_C)tools.c $(SRCS_C)cycle_to_die.c \
	$(SRCS_C)rm_element.c $(SRCS_C)params.c $(SRCS_C)coding_byte.c \
	$(SRCS_C)instruct_1to5.c $(SRCS_C)instruct_6to10.c \
	$(SRCS_C)instruct_11to15.c $(SRCS_C)instruct_16.c

INC = include/

OBJ_C = $(addprefix ,$(S_C:.c=.o))

L_FT = ./Libft
LIB_LNK = -L $(L_FT) -lft
LIB_INC	= -I $(L_FT)

P_FT = ./ft_printf
P_LNK = -L $(P_FT) -lftprintf
P_INC	= -I $(P_FT)/includes

FLAGS = -Werror -Wextra -Wall

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ_C)
	@make -C ft_printf/
	@make -C Libft/
	@gcc $(OBJ_C) $(P_INC) $(LIB_INC) -I $(INC) $(FLAGS) -o $(NAME) $(LIB_LNK) $(P_LNK)
	@echo "\n\033[32;01m./corewar.. done !\033[00m\n"

%.o:%.c $(INC)
	@gcc -I $(INC) $(FLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_C)
	@ cd ft_printf && make clean
	@ cd Libft && make clean
	@echo "\n\033[31;01mClean..\033[00m\n"

fclean: clean
	@rm -rf $(NAME)
	@ cd ft_printf && make fclean
	@ cd Libft && make fclean
	@echo "\n\033[31;01mFclean..\033[00m\n"

re: fclean all
