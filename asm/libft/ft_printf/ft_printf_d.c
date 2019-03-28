/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf_d.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: quruiz <quruiz@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/19 12:05:36 by quruiz       #+#   ##    ##    #+#       */
/*   Updated: 2018/04/07 02:59:59 by quruiz      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_printf_d_simple(t_sgmt *box, int neg, char *str, int lennbr)
{
	char *res;

	if (str[0] == '0' && FLAGS->dot)
		str = ft_strdup("\0");
	if (neg)
		res = ft_conncat(ft_strdup("-"), str, 1, lennbr);
	else if (!FLAGS->plus && FLAGS->space)
		res = ft_conncat(ft_strdup(" "), str, 1, lennbr);
	else if (FLAGS->plus)
		res = ft_conncat(ft_strdup("+"), str, 1, lennbr);
	else
		res = ft_strdup(str);
	return (res);
}

char	*ft_printf_d(t_sgmt *box, va_list arg)
{
	intmax_t	tmp;
	char		*str;
	char		*ret;
	int			neg;

	neg = 0;
	ft_get_signed_arg(&tmp, box, arg);
	neg = tmp < 0 ? 1 : 0;
	if (neg)
		FLAGS->plus = 0;
	str = ft_itoa_pf(tmp * (neg ? -1 : 1));
	if (FLAGS->prec && FLAGS->wid == 0)
		ret = ft_printf_d_prec(box, neg, str, (ft_strlen(str)));
	else if (FLAGS->wid > 0 && FLAGS->prec <= 0)
		ret = ft_printf_d_wid(box, neg, str, (ft_strlen(str) + neg));
	else if (FLAGS->wid < 0 && FLAGS->prec == 0)
		ret = ft_printf_d_wid_neg(box, neg, str, (ft_strlen(str) + neg));
	else if (FLAGS->wid > 0 && (FLAGS->prec != 0 || FLAGS->dot))
		ret = (ft_printf_d_pos(box, neg, str, (ft_strlen(str) + neg)));
	else if (FLAGS->wid < 0 && FLAGS->prec != 0)
		ret = (ft_printf_d_neg(box, neg, str, ft_strlen(str)));
	else
		ret = ft_printf_d_simple(box, neg, str, (ft_strlen(str)));
	free(str);
	return (ret);
}
