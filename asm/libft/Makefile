# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: quruiz <quruiz@student.le-101.fr>          +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/01/18 12:41:18 by quruiz       #+#   ##    ##    #+#        #
#    Updated: 2019/03/25 18:03:25 by quruiz      ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME = libft.a
FLAG = -Werror -Wall -Wextra
HEADER = libft/libft.h get_next_line/get_next_line.h
LIBFT_SRC = ft_atoi.c ft_bzero.c ft_conncat.c ft_intlen.c ft_isalnum.c \
	ft_isalpha.c ft_isascii.c ft_isdigit.c ft_islower.c ft_isprint.c \
	ft_isupper.c ft_itoa.c ft_itoa_base.c ft_lstadd.c ft_lstdel.c \
	ft_lstdelone.c ft_lstiter.c ft_lstmap.c ft_lstnew.c ft_memalloc.c \
	ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memdel.c ft_memmove.c \
	ft_memset.c ft_putchar.c ft_putchar_fd.c ft_putendl.c ft_putendl_fd.c \
	ft_putnbr.c ft_putnbr_fd.c ft_putnstr_fd.c ft_putnwstr_fd.c ft_putstr.c \
	ft_putstr_fd.c ft_putstrchar.c ft_putwchar.c ft_putwchar_fd.c ft_putwstr.c \
	ft_putwstr_fd.c ft_recursive_factorial.c ft_recursive_power.c ft_sqrt.c \
	ft_str_is_alpha.c ft_str_is_lowercase.c ft_str_is_numeric.c \
	ft_str_is_printable.c ft_str_is_uppercase.c ft_str_realloc.c \
	ft_strcapitalize.c ft_strcat.c ft_strchr.c ft_strclr.c ft_strcmp.c \
	ft_strcpy.c ft_strdel.c ft_strdup.c ft_strequ.c ft_striter.c ft_striteri.c \
	ft_strjoin.c ft_strlcat.c ft_strlen.c ft_strlowcase.c ft_strmap.c ft_strmapi.c \
	ft_strncat.c ft_strncmp.c ft_strncpy.c ft_strnequ.c ft_strnew.c ft_strnstr.c \
	ft_strrchr.c ft_strrev.c ft_strsplit.c ft_strstr.c ft_strsub.c ft_strtrim.c \
	ft_strupcase.c ft_swap.c ft_tab_realloc.c ft_tolower.c ft_toupper.c \
	ft_wcharlen.c ft_wstrdup.c ft_wstrlen.c ft_freesplit.c ft_putsplit.c \
	ft_add_line_to_tab.c ft_free_line.c ft_atoui.c ft_check_limit.c ft_uitoa.c \
	ft_uintlen.c ft_split_whitespaces.c ft_bswap_int32.c ft_bswap_int16.c \
	ft_str_is_empty.c ft_strsplit_trim.c ft_isnotprint.c
GNL_SRC = get_next_line/get_next_line.c
SRC = $(addprefix libft/, $(LIBFT_SRC)) $(GNL_SRC)
OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c $(HEADER)
		@gcc $(FLAG) -c $< -o $@

$(NAME): $(OBJ)
		@ar rc $(NAME) $(OBJ) $@ $^
		@ranlib $(NAME)

clean:
		@rm -f $(OBJ)

fclean: clean
		@rm -f $(NAME)

re: fclean all
