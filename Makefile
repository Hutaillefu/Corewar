# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: quruiz <quruiz@student.le-101.fr>          +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2019/03/07 17:49:02 by quruiz       #+#   ##    ##    #+#        #
#    Updated: 2019/03/27 15:51:32 by quruiz      ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME = GOD

ASM = 		./asm/
COREWAR = 	./vm/

all: $(NAME)

$(NAME):
		@make -C $(ASM)
		@make -C $(COREWAR)

clean:
		@make clean -C $(ASM)
		@make clean -C $(COREWAR)			

fclean: clean
		@make fclean -C $(ASM)
		@make fclean -C $(COREWAR)

re: fclean all