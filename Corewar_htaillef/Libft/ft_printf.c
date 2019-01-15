/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/13 09:36:41 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/05 10:46:29 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/ft_printf.h"

int		ft_args(const char *format, va_list args, t_prnt *p)
{
	int conv;
	int flg;

	conv = 0;
	flg = 0;
	p->conv = 0;
	if (format[p->i])
		p->i++;
	if (format[p->i] == '\0')
		p->f = 1;
	reinit_prnt(p);
	while (conv == 0 && format[p->i])
	{
		flg = 0;
		flg = ft_flag(format, p, args);
		if (flg == 0)
			conv = ft_conversion(format, args, 0, p);
		if (conv == -1)
			return (-1);
		if (conv == -2)
			p->conv = 1;
		if (conv == 0 && format[p->i] != '\0')
			p->i++;
	}
	return (1);
}

int		ft_printf(const char *restrict format, ...)
{
	va_list	args;
	t_prnt	*p;
	int		ret;

	va_start(args, format);
	p = init_prnt();
	while (format[p->i])
	{
		if (ft_printf_next(p, format, args) == -1)
		{
			free(p);
			return (-1);
		}
	}
	ret = p->buf + p->ret;
	ft_putstr_p(p->str, p);
	va_end(args);
	if (p != NULL)
		free(p);
	return (ret);
}

int		ft_printf_next(t_prnt *p, const char *format, va_list args)
{
	if (format[p->i] == '%')
	{
		if (ft_args(format, args, p) == -1)
			return (-1);
	}
	else
	{
		p->tmp = 0;
		while (format[p->i] && format[p->i] != '%')
		{
			ft_print_nf(p, format);
			p->i++;
			p->tmp++;
			p->conv = 0;
		}
		p->i--;
	}
	if (format[p->i] && p->conv == 0)
		p->i++;
	return (0);
}

void	ft_print_nf(t_prnt *p, const char *format)
{
	if (p->wdth > 0 && p->neg == 0 && p->conv == 1)
	{
		while (p->wdth-- > 1)
		{
			if (p->zro == 0)
				ft_putchar_p(' ', p);
			else
				ft_putchar_p('0', p);
		}
		ft_putchar_p(format[p->i], p);
	}
	else if (p->wdth > 0 && p->neg == 1 && p->conv == 1)
	{
		ft_putchar_p(format[p->i], p);
		while (p->wdth-- > 1)
		{
			if (p->zro == 0)
				ft_putchar_p(' ', p);
			else
				ft_putchar_p('0', p);
		}
	}
	else
		ft_putchar_p(format[p->i], p);
}
