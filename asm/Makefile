# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: quruiz <quruiz@student.le-101.fr>          +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2019/03/07 17:49:02 by quruiz       #+#   ##    ##    #+#        #
#    Updated: 2019/03/13 15:08:33 by quruiz      ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME = asm
LIBFT = libft/libft.a
HEADER = include/asm.h include/op.h
FLAG = -Werror -Wall -Wextra -ggdb
SRC = src/asm.c src/destructor.c src/encode.c src/error.c src/get_header.c \
	src/get_label.c src/get_op.c src/handlers.c src/op.c src/utils.c \
	src/write_cor.c src/parser.c
OBJ = $(SRC:.c=.o)

all: lib $(NAME)

%.o: %.c $(HEADER)
				@gcc $(FLAG) -c $< -o $@

lib:
				@make -C libft

$(NAME): $(OBJ) $(LIBFT)
				@gcc $(FLAG) $(OBJ) $(LIBFT) -o $(NAME)

clean:
				@make clean -C libft/
				@rm -f $(OBJ)

fclean: clean
				@rm -rf $(NAME).dSYM/
				@make fclean -C libft/
				@rm -f $(NAME)

git: fclean
				@read -ep "Files to commit: " file && git add $$file
				@read -p "Commit message: " msg && git commit -m "$$msg"
				@git push

re: fclean all