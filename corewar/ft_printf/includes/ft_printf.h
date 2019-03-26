/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: htaillef <htaillef@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/05 16:01:43 by htaillef     #+#   ##    ##    #+#       */
/*   Updated: 2018/02/20 17:21:33 by htaillef    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <wchar.h>

# define LOGS_LEN 10240

typedef struct	s_logs
{
	char	*buffer;
	int		len;
}				t_logs;

int				init_logs(t_logs *logs);
void			add_logs(t_logs *logs, char *log);
void			dump_logs(t_logs *logs);

int					ft_printf(t_logs *logs, const char *restrict format, ...);

enum				e_bool
{
	FALSE = 0,
	TRUE = 1
};

typedef struct		s_flags
{
	enum e_bool		left_justify;
	enum e_bool		padding;
	enum e_bool		positive;
	enum e_bool		blank;
	enum e_bool		diese;
}					t_flags;

typedef	union		u_type
{
	int			t_int;
	long		t_long;
	long long	t_long_long;
	size_t		t_size_t;
	intmax_t	t_intmax_t;
	char		t_char;
	short		t_short;
}					t_type;

typedef struct		s_format
{
	t_flags			*flags;
	size_t			min_width;
	enum e_bool		period;
	size_t			precision;
	char			*modifier;
	char			type;
	enum e_bool		is_numeric;
	enum e_bool		is_negative;
}					t_format;

void				ft_putchar_fd(char c, int fd);
void				ft_putchar(char c);
void				ft_putnbr_fd(int n, int fd);
void				ft_putnbr(int n);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putstr(char const *s);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
size_t				ft_strlen(const char *s);
int					ft_isdigit(int c);
int					ft_atoi(const char *str);
char				*ft_strdup(const char *s1);
char				*ft_strcpy(char *dst, const char *src);
int					ft_strcmp(const char *s1, const char *s2);
void				ft_bzero(void *s, size_t n);
void				*ft_memalloc(size_t size);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strncat(char *dst, const char *src, size_t n);
char				*ft_itoall(long long n);
char				*ft_itoaull(unsigned long long n);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strncpy(char *dst, const char *src, size_t len);
void				ft_memdel(void **ap);

char				*ft_strnjoin(char *s1, char const *s2, size_t n);
char				*ft_itoall_base(long long n, int base, enum e_bool capital);
char				*ft_itoaull_base(unsigned long long n, long long base,
	enum e_bool capital);

t_format			*new_format(void);
t_format			*extract(char **str);
void				free_format(t_format **format);

int					display_format(t_format *infos, va_list *args, t_logs *logs);

int					wcharlen(wchar_t wchar);
char				*wchartostr(wchar_t wchar);

char				*process_int(t_format *infos, void *value);
char				*process_uint(t_format *infos, void *value);
char				*process_hexa(t_format *infos, void *value);
char				*process_octal(t_format *infos, void *value);

char				*process_string(void *value);
char				*process_char(void *value);
char				*process_wchar(void *value);
char				*process_wstr(void *value);

char				*ft_init(size_t len, char c);
void				ft_write(char **src, char *new, size_t start_index);
void				customput(char *final);

void				check_flags(char **str, t_format **format);
void				check_width(char **str, size_t *val);
void				check_modifier(char **str, t_format **format);
void				check_period(char **str, t_format **format);
void				check_type(char **str, t_format **format);

char				*process_type_with_modifier(t_format *infos, va_list *args);
void				process_add_buffer(char **add, t_format *format, char *res);
void				process_precision(char **res, t_format *format);
enum e_bool			process_final(char **final, char *res, t_format *format,
	char *add);

#endif
