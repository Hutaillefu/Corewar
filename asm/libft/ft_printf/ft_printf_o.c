/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf_o.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: quruiz <quruiz@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/24 22:48:42 by quruiz       #+#   ##    ##    #+#       */
/*   Updated: 2018/04/04 02:21:08 by quruiz      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_printf_o_simple(t_sgmt *box, char *str)
{
	char	*res;

	if (FLAGS->sharp && FLAGS->sharp)
		res = ft_conncat(ft_strdup("0"), str, 1, ft_strlen(str));
	else
		res = ft_strdup(str);
	return (res);
}

char	*ft_printf_o_choose(t_sgmt *box, char *str)
{
	char	*res;

	if (FLAGS->prec && FLAGS->wid == 0)
		res = ft_printf_o_prec(box, str, ft_strlen(str));
	else if (FLAGS->wid != 0 && FLAGS->prec == 0)
		res = ft_printf_o_wid(box, str, ft_strlen(str) + FLAGS->sharp);
	else if (FLAGS->wid > 0 && FLAGS->prec != 0)
		res = ft_printf_o_pos(box, str, ft_strlen(str));
	else if (FLAGS->wid < 0 && FLAGS->prec != 0)
		res = ft_printf_o_neg(box, str, ft_strlen(str));
	else
		res = ft_printf_o_simple(box, str);
	return (res);
}

char	*ft_printf_o(t_sgmt *box, int base, va_list arg)
{
	uintmax_t	tmp;
	char		*str;
	char		*res;
	char		*wid;
	char		c;

	c = ' ';
	if (FLAGS->zero)
		c = ((FLAGS->space) ? ' ' : '0');
	tmp = 0;
	wid = ft_putstrchar((FLAGS->wid - FLAGS->sharp), c);
	ft_get_unsigned_arg(&tmp, box, arg);
	if (!tmp && FLAGS->wid && FLAGS->sharp && !FLAGS->dot)
		return (ft_conncat(wid, "0", ft_strlen(wid), 1));
	if (!tmp && FLAGS->wid && FLAGS->dot && !FLAGS->prec)
		return (wid);
	if (!tmp && FLAGS->sharp && !FLAGS->wid && !FLAGS->prec)
		return (ft_strdup("0"));
	if (!tmp && FLAGS->dot && !FLAGS->prec)
		return (ft_strdup("\0"));
	str = ft_itoa_base(tmp, base);
	res = ft_printf_o_choose(box, str);
	free(wid);
	free(str);
	return (res);
}
