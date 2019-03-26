# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2017/11/23 14:26:48 by gzanarel     #+#   ##    ##    #+#        #
#    Updated: 2019/01/15 13:22:08 by gzanarel    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME = libft.a

SRC = ft_memset.c \
	ft_memalloc.c \
	ft_memdel.c \
	ft_strnew.c \
	ft_strdel.c \
	ft_strclr.c \
	ft_striter.c \
	ft_striteri.c \
	ft_strmap.c \
	ft_strmapi.c \
	ft_strlen.c \
	ft_strequ.c \
	ft_strnequ.c \
	ft_strsub.c \
	ft_bzero.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_strdup.c \
	ft_memccpy.c \
	ft_strcpy.c \
	ft_strncpy.c \
	ft_strcat.c \
	ft_strncat.c \
	ft_strlcat.c \
	ft_strchr.c \
	ft_strrchr.c \
	ft_strstr.c \
	ft_strnstr.c \
	ft_strcmp.c \
	ft_strncmp.c \
	ft_atoi.c \
	ft_isalpha.c \
	ft_isdigit.c \
	ft_isalnum.c \
	ft_isascii.c \
	ft_isprint.c \
	ft_toupper.c \
	ft_tolower.c \
	ft_strjoin.c \
	ft_strtrim.c \
	ft_putchar.c \
	ft_putstr.c \
	ft_putendl.c \
	ft_putnbr.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_nbrlen.c \
	ft_itoa.c \
	ft_strsplit.c \
	ft_lstnew.c \
	ft_lstdelone.c \
	ft_lstdel.c \
	ft_lstadd.c \
	ft_lstiter.c \
	ft_lstmap.c \
	ft_swap.c \
	ft_islower.c \
	ft_isupper.c \
	ft_strndup.c \
	get_next_line.c \
	ft_atol.c \
	free_2d.c \
	ft_realloc.c \
	ft_memsub.c \

HDR = includes/

CFLAGS = -Wall -Wextra -Werror

OBJ = $(patsubst %.c, objs/%.o, $(SRC))

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)
	@echo "\n\033[32;01mlibft.a.. done !\033[00m\n"

objs/%.o: %.c $(HDR)
	@mkdir -p objs/
	@gcc $(CFLAGS) -c -o $@ $<

.Phony: all

clean:
	@rm -f objs/*.o
	@rm -rf objs/

fclean: clean
	@rm -f $(NAME)

re: fclean all
