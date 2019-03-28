/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf_x.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: quruiz <quruiz@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/18 20:07:00 by quruiz       #+#   ##    ##    #+#       */
/*   Updated: 2018/04/07 17:41:55 by quruiz      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_printf_x_simple(t_sgmt *box, char *str, int len)
{
	char	*res;

	if (FLAGS->sharp)
		res = ft_conncat(ft_strdup("0x"), str, 2, len);
	else
		res = ft_strsub(str, 0, ft_strlen(str));
	return (res);
}

char	*ft_printf_x_choose(t_sgmt *box, char *str)
{
	char	*res;
	int		len;

	len = ft_strlen(str);
	if (FLAGS->prec && FLAGS->wid == 0)
		res = ft_printf_x_prec(box, str, len);
	else if (FLAGS->wid != 0 && FLAGS->prec == 0)
		res = ft_printf_x_wid(box, str, len + (FLAGS->sharp ? 2 : 0));
	else if (FLAGS->wid > 0 && FLAGS->prec != 0)
		res = ft_printf_x_pos(box, str, len);
	else if (FLAGS->wid < 0 && FLAGS->prec != 0)
		res = ft_printf_x_neg(box, str, len);
	else
		res = ft_printf_x_simple(box, str, ft_strlen(str));
	free(str);
	return (res);
}

char	*ft_printf_x(t_sgmt *box, int base, va_list arg)
{
	uintmax_t	tmp;
	char		*str;
	char		*res;
	char		*wid;
	char		c;

	tmp = 0;
	c = FLAGS->zero ? '0' : ' ';
	wid = ft_putstrchar((FLAGS->wid - FLAGS->sharp), c);
	ft_get_unsigned_arg(&tmp, box, arg);
	if (!tmp)
	{
		if (FLAGS->wid)
			return (ft_putstrchar(FLAGS->wid, c));
		else if (FLAGS->dot && !FLAGS->prec)
			return (ft_strdup("\0"));
		else
			return (ft_strdup("0"));
	}
	str = ft_itoa_base(tmp, base);
	res = ft_printf_x_choose(box, str);
	free(wid);
	if (FLAGS->type == 'X')
		res = ft_strupcase(res);
	return (res);
}

char	*ft_printf_p_choose(t_sgmt *box, char *str)
{
	char	*res;
	int		len;

	len = ft_strlen(str) + 2;
	if (FLAGS->prec && FLAGS->wid == 0)
		res = ft_printf_p_prec(box, str, len);
	else if (FLAGS->wid != 0 && FLAGS->prec == 0)
		res = ft_printf_p_wid(box, str, len);
	else if (FLAGS->wid > 0 && FLAGS->prec != 0)
		res = ft_printf_p_pos(box, str, len);
	else if (FLAGS->wid < 0 && FLAGS->prec != 0)
		res = ft_printf_p_neg(box, str, len);
	else
		res = ft_conncat(ft_strdup("0x"), str, 2, len);
	return (res);
}

char	*ft_printf_p(t_sgmt *box, int base, va_list arg)
{
	uintmax_t	tmp;
	char		*str;
	char		*res;
	char		*prec;

	tmp = 0;
	tmp = va_arg(arg, uintmax_t);
	str = ft_itoa_base(tmp, base);
	if (!tmp && FLAGS->wid == 0)
	{
		if (FLAGS->prec != 0 || FLAGS->dot)
		{
			prec = ft_putstrchar(FLAGS->prec, '0');
			res = ft_conncat(ft_strdup("0x"), prec, 2, FLAGS->prec);
			free(prec);
		}
		else
			res = ft_strdup("0x0");
	}
	else
		res = ft_printf_p_choose(box, str);
	free(str);
	return (res);
}
