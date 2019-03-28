/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: quruiz <quruiz@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/13 14:17:01 by quruiz       #+#   ##    ##    #+#       */
/*   Updated: 2019/03/27 14:05:33 by quruiz      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include "../libft/libft.h"

# define FLAGS		box->flag
# define RED		"\x1b[31m"
# define GREEN		"\x1b[32m"
# define YELLOW		"\x1b[33m"
# define BLUE		"\x1b[34m"
# define MAGENTA	"\x1b[35m"
# define CYAN		"\x1b[36m"
# define RESET		"\x1b[0m"

typedef struct		s_flag
{
	int			prec;
	int			wid;
	int			sharp;
	int			zero;
	int			moins;
	int			plus;
	int			space;
	int			h;
	int			l;
	int			j;
	int			z;
	int			dot;
	int			type;
}					t_flag;

typedef	struct		s_sgmt
{
	t_flag			*flag;
	char			*str;
	int				i;
	int				set;
	int				err;
	int				fd;
	int				c;
	struct s_sgmt	*next;
}					t_sgmt;

int					ft_printf(char *format, ...);
int					ft_dprintf(int fd, char *format, ...);
/*
**Utilities
*/
void				ft_format_cutter(t_sgmt *box, char *tmp, int fd);
int					ft_flag_detect(t_sgmt *box, va_list arg);
void				ft_main_parsing(t_sgmt *box, va_list arg);
void				ft_dispatch(t_sgmt *box, va_list arg);
char				*ft_wcharstr(wchar_t c, int len);
char				*ft_wchar_to_char(wchar_t *s, char *res, int len);
int					ft_printing(t_sgmt *box);
void				ft_get_unsigned_arg
					(uintmax_t *tmp, t_sgmt *box, va_list arg);
void				ft_get_signed_arg(intmax_t *tmp, t_sgmt *box, va_list arg);
int					ft_get_wchar_len(wchar_t c);
char				*ft_itoa_pf(intmax_t n);
/*
**Conversion
*/
char				*ft_printf_s(t_sgmt *box, va_list arg);
char				*ft_printf_c(t_sgmt *box, va_list arg);
char				*ft_printf_c_wid(t_sgmt *box, char *s);
char				*ft_printf_percent(t_sgmt *box);
char				*ft_printf_p(t_sgmt *box, int base, va_list arg);
char				*ft_printf_p_choose(t_sgmt *box, char *str);
char				*ft_printf_p_prec(t_sgmt *box, char *str, int lennbr);
char				*ft_printf_p_pos(t_sgmt *box, char *str, int lennbr);
char				*ft_printf_p_neg(t_sgmt *box, char *str, int lennbr);
char				*ft_printf_p_wid_neg(t_sgmt *box, char *str, int lennbr);
char				*ft_printf_p_wid(t_sgmt *box, char *str, int lennbr);
char				*ft_printf_x(t_sgmt *box, int base, va_list arg);
char				*ft_printf_x_prec(t_sgmt *box, char *str, int lennbr);
char				*ft_printf_x_pos(t_sgmt *box, char *str, int lennbr);
char				*ft_printf_x_neg(t_sgmt *box, char *str, int lennbr);
char				*ft_printf_x_wid_neg(t_sgmt *box, char *str, int lennbr);
char				*ft_printf_x_wid(t_sgmt *box, char *str, int lennbr);
char				*ft_printf_o(t_sgmt *box, int base, va_list arg);
char				*ft_printf_o_prec(t_sgmt *box, char *str, int lennbr);
char				*ft_printf_o_pos(t_sgmt *box, char *str, int lennbr);
char				*ft_printf_o_neg(t_sgmt *box, char *str, int lennbr);
char				*ft_printf_o_wid_neg(t_sgmt *box, char *str, int lennbr);
char				*ft_printf_o_wid(t_sgmt *box, char *str, int lennbr);
char				*ft_printf_d(t_sgmt *box, va_list arg);
char				*ft_printf_d_wid
					(t_sgmt *box, int neg, char *str, int lennbr);
char				*ft_printf_d_wid_neg
					(t_sgmt *box, int neg, char *str, int lennbr);
char				*ft_printf_d_prec
					(t_sgmt *box, int neg, char *str, int lennbr);
char				*ft_printf_d_neg
					(t_sgmt *box, int neg, char *str, int lennbr);
char				*ft_printf_d_pos
					(t_sgmt *box, int neg, char *str, int lennbr);
#endif
