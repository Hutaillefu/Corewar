/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_conversion.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/29 12:47:46 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/05 10:46:02 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/ft_printf.h"

int		ft_conversion(const char *format, va_list args, int ret, t_prnt *p)
{
	if (!(ft_strchr("%sSpdDioOuUxXcC", format[p->i])))
		return (-2);
	if (((format[p->i] != '%' && format[p->i] != 'c') && p->got_prcs == 1 &&
	format[p->i] != 'S' && format[p->i] != 's'))
		p->zro = 0;
	if (format[p->i] == 's')
	{
		if (p->l == 1)
			ret = ft_conv_bs(args, p);
		else
			ret = ft_conv_s(args, p, format);
	}
	if (format[p->i] == 'S')
		ret = ft_conv_bs(args, p);
	if (format[p->i] == 'p')
		ret = ft_conv_p(args, p, format);
	if (format[p->i] == 'd' || format[p->i] == 'i' || format[p->i] == 'D')
	{
		if (format[p->i] == 'D')
			p->l = 1;
		ret = ft_conv_d(args, p, format);
	}
	if (ret == 0)
		ret = ft_conversion_ftr(format, args, ret, p);
	return (ret);
}

int		ft_conversion_ftr(const char *format, va_list args, int ret, t_prnt *p)
{
	if (format[p->i] == 'u' || format[p->i] == 'U')
	{
		if (format[p->i] == 'U')
			p->l = 1;
		ret = ft_conv_u(args, p, format);
	}
	if (format[p->i] == 'x' || format[p->i] == 'X')
		ret = ft_conv_x(args, p, format);
	if (format[p->i] == 'c')
	{
		if (p->l == 1)
			ret = ft_conv_bc(args, p);
		else
			ret = ft_conv_c(args, p, format);
	}
	if (format[p->i] == 'C')
		ret = ft_conv_bc(args, p);
	if (ret == 0)
		ret = ft_conv_ftr_2(format, args, ret, p);
	return (ret);
}

int		ft_conv_ftr_2(const char *format, va_list args, int ret, t_prnt *p)
{
	if (format[p->i] == '%')
		ret = ft_conv_prc(p, format);
	if (format[p->i] == 'o' || format[p->i] == 'O')
	{
		if (format[p->i] == 'O')
			p->l = 1;
		ret = ft_conv_o(args, p, format);
	}
	return (ret);
}
