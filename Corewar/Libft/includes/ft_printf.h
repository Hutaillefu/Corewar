/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/13 09:36:37 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/05 10:43:59 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <locale.h>
# include <wchar.h>
# include "libft.h"

typedef struct	s_prnt
{
	int			ret;
	int			sgn_nb;
	char		*arg;
	char		spe;
	char		str[4096];
	int			hst;
	int			hstx;
	int			pls;
	int			neg;
	int			got_wdth;
	int			wdth;
	int			zro;
	int			prcs;
	int			space;
	int			got_prcs;
	int			i;
	int			l;
	int			ll;
	int			h;
	int			hh;
	int			buf;
	int			j;
	int			z;
	int			mdf;
	int			tmp;
	int			conv;
	int			wczro;
	int			f;
}				t_prnt;

/*
** printf
*/
int				ft_printf(const char *restrict format, ...);
int				ft_args(const char *format, va_list args, t_prnt *p);
void			ft_print_nf(t_prnt *p, const char *format);
int				ft_printf_next(t_prnt *p, const char *format, va_list args);

/*
** ft_itoa
*/
char			*ft_itoa_base_low(uintmax_t n, int base);
char			*ft_itoa_base_up(uintmax_t n, int base);
unsigned int	ft_nbrlen_base(uintmax_t n, int base);

/*
** libft
*/
char			*ft_strncpy(char *dst, const char *src, size_t len);
size_t			ft_strlen(char *str);
int				ft_isdigit(int c);
char			*ft_strchr(const char *s, int c);
void			ft_putstr_p(char const *s, t_prnt *p);
void			ft_putchar_p(char s, t_prnt *p);
void			ft_putchar_wp(wchar_t c, t_prnt *p);
char			*ft_strsub(char const *s, unsigned int start, size_t len);

/*
** conversion
*/
int				ft_conversion(const char *ft, va_list args, int ret, t_prnt *p);
int				ft_conversion_ftr(const char *f, va_list a, int rt, t_prnt *p);
int				ft_conv_ftr_2(const char *ft, va_list as, int rt, t_prnt *p);

/*
** char
*/
int				ft_conv_s(va_list args, t_prnt *p, const char *format);
int				ft_conv_c(va_list args, t_prnt *p, const char *format);
int				ft_conv_bs(va_list args, t_prnt *p);
int				ft_conv_bc(va_list args, t_prnt *p);
int				ft_conv_prc(t_prnt *p, const char *format);
char			*ft_modif_wchar_to_char(wchar_t *ws, t_prnt *p);
char			*ft_modif_wchar_next(wchar_t *ws, int len, t_prnt *p);

/*
** numb
*/
int				ft_conv_p(va_list args, t_prnt *p, const char *format);
int				ft_conv_d(va_list args, t_prnt *p, const char *format);
int				ft_conv_o(va_list args, t_prnt *p, const char *format);
int				ft_conv_u(va_list args, t_prnt *p, const char *format);
int				ft_conv_x(va_list args, t_prnt *p, const char *format);

/*
** flags
*/
int				ft_flag(const char *format, t_prnt *p, va_list args);
int				ft_precision(const char *format, t_prnt *p, va_list args);
int				ft_wdth(const char *format, t_prnt *p, va_list args);
int				ft_modif(const char *format, t_prnt *p);
int				ft_lenght(const char *format, t_prnt *p);

/*
** tools
*/
char			*ft_error(char *str);
t_prnt			*init_prnt(void);
void			init_prnt_2(t_prnt *p);
void			reinit_prnt(t_prnt *p);
void			ft_save_str(char c, t_prnt *p);

/*
** display char
*/
int				ft_display_char(t_prnt *p);
void			ft_print_wdth_char(t_prnt *p);
void			ft_print_prcs_char(t_prnt *p);
void			ft_print_neg_char(t_prnt *p);
void			ft_print_zro_char(t_prnt *p);

/*
** display numb
*/
void			ft_print_wdth(t_prnt *p);
void			ft_print_neg(t_prnt *p);
void			ft_print_prcs(t_prnt *p, int wdth);
void			ft_print_prcsww(t_prnt *p);
int				ft_display_numb(t_prnt *p);

/*
** display
*/
void			ft_print_hst(t_prnt *p);
void			ft_print_space(t_prnt *p);
void			ft_print_zro(t_prnt *p);
void			ft_print_zro_ftr(t_prnt *p, int wdth);
void			ft_display_arg(t_prnt *p);

/*
** check
*/
char			*ft_check_usgnd(t_prnt *p, va_list args);
char			*ft_check_sgnd(t_prnt *p, va_list args);

/*
** utils
*/
int				ft_wstrlen(wchar_t *wstr);
int				ft_wclen(wchar_t c);
char			*ft_putchar_to_char(wchar_t c);
int				ft_check_wchar(wchar_t c);
int				ft_putwchar_to_char(wchar_t c, char *str, int i);
int				ft_putwchar_to_char_2(wchar_t c, char *str, int i, int len);
char			*ft_putchar_to_char_2(wchar_t c, char *str, int i);

#endif
