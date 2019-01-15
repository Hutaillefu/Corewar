/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_flags.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/20 18:59:24 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/05 10:45:40 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/ft_printf.h"

int		ft_modif(const char *format, t_prnt *p)
{
	if (format[p->i] == '#')
		p->hst = 1;
	else if (format[p->i] == '0' && p->got_prcs == 0)
		p->zro = 1;
	else if (format[p->i] == '-')
		p->neg = 1;
	else if (format[p->i] == '+')
		p->pls = 1;
	else if (format[p->i] == ' ')
		p->space = 1;
	return (1);
}

int		ft_lenght(const char *format, t_prnt *p)
{
	int i;

	i = p->i;
	if (format[i] == 'l')
	{
		p->ll = (format[++i] == 'l') ? 1 : 0;
		p->l = (format[i] != 'l') ? 1 : 0;
		if (p->ll == 1)
			p->i++;
	}
	if (format[i] == 'h')
	{
		p->hh = (format[++i] == 'h') ? 1 : 0;
		p->h = (format[i] != 'h') ? 1 : 0;
		if (p->hh == 1)
			p->i++;
	}
	if (format[i] == 'j')
		p->j = 1;
	if (format[i] == 'z')
		p->z = 1;
	return (1);
}

int		ft_wdth(const char *format, t_prnt *p, va_list args)
{
	if (format[p->i] == '*')
	{
		p->wdth = va_arg(args, int);
		if (p->wdth < 0)
		{
			p->wdth = -p->wdth;
			p->neg = 1;
		}
		p->got_wdth = 1;
	}
	else
	{
		while (ft_isdigit(format[p->i]))
		{
			p->wdth = p->wdth * 10 + (format[p->i++] - '0');
			p->got_wdth = 1;
		}
		p->i -= 1;
	}
	return (1);
}

int		ft_precision(const char *format, t_prnt *p, va_list args)
{
	p->i++;
	if (format[p->i] == '*')
	{
		p->prcs = va_arg(args, int);
		if (p->prcs < 0)
		{
			p->prcs = -p->prcs;
			p->neg = 1;
		}
		p->got_prcs = 1;
	}
	else
	{
		if (!ft_isdigit(format[p->i]))
			p->prcs = 0;
		while (ft_isdigit(format[p->i]))
			p->prcs = p->prcs * 10 + (format[p->i++] - '0');
		p->got_prcs = 1;
		p->i -= 1;
	}
	return (1);
}

int		ft_flag(const char *format, t_prnt *p, va_list args)
{
	int ret;

	ret = 0;
	if (ft_strchr("#0-+ ", format[p->i]))
		ret = ft_modif(format, p);
	else if (format[p->i] == '.')
		ret = ft_precision(format, p, args);
	else if ((ft_isdigit(format[p->i]) && format[p->i] != '0')
	|| format[p->i] == '*')
		ret = ft_wdth(format, p, args);
	else if (ft_strchr("hljz", format[p->i]))
		ret = ft_lenght(format, p);
	else
		ret = 0;
	return (ret);
}
