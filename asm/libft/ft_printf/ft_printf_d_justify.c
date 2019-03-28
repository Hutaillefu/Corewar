/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf_d_justify.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: quruiz <quruiz@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/20 16:53:07 by quruiz       #+#   ##    ##    #+#       */
/*   Updated: 2018/04/09 19:14:27 by quruiz      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_printf_d_pos(t_sgmt *box, int neg, char *str, int lennbr)
{
	int		lenspc;
	int		lenzero;
	char	*res;
	char	*prec;

	if (FLAGS->wid < FLAGS->prec)
		return (ft_printf_d_prec(box, neg, str, lennbr - neg));
	lennbr -= neg;
	lenzero = (FLAGS->prec <= lennbr) ? 0 : (FLAGS->prec - (lennbr));
	lenspc = FLAGS->wid - (lenzero + lennbr + neg);
	if (str[0] == '0')
		str[0] = (FLAGS->dot && FLAGS->prec) ? '0' : ' ';
	lenspc -= (FLAGS->plus && !neg) ? 1 : 0;
	res = ft_putstrchar(lenspc, ' ');
	if (neg)
		res = ft_conncat(res, "-", ft_strlen(res), 1);
	else if (FLAGS->plus)
		res = ft_conncat(res, "+", ft_strlen(res), 1);
	if (lenzero > 0)
	{
		prec = ft_putstrchar(lenzero, '0');
		res = ft_conncat(res, prec, ft_strlen(res), lenzero);
		free(prec);
	}
	return (ft_conncat(res, str, ft_strlen(res), lennbr));
}

char	*ft_printf_d_neg(t_sgmt *box, int neg, char *str, int lennbr)
{
	int		lenspc;
	int		lenzero;
	char	*res;
	char	*wid;
	char	*prec;

	res = NULL;
	FLAGS->wid *= -1;
	if (FLAGS->wid < FLAGS->prec)
		return (ft_printf_d_prec(box, neg, str, lennbr));
	lenspc = FLAGS->wid - FLAGS->prec - ((FLAGS->plus || neg) ? 1 : 0);
	lenzero = (FLAGS->prec <= lennbr) ? 0 : (FLAGS->prec - lennbr);
	if (neg)
		res = ft_strdup("-");
	else if (FLAGS->plus)
		res = ft_strdup("+");
	prec = ft_putstrchar(lenzero, '0');
	wid = ft_putstrchar(lenspc, ' ');
	res = ft_conncat(res, prec, ((FLAGS->plus || neg) ? 1 : 0), lenzero);
	res = ft_conncat(res, str, ft_strlen(res), lennbr);
	res = ft_conncat(res, wid, ft_strlen(res), lenspc);
	free(wid);
	free(prec);
	return (res);
}

char	*ft_printf_d_prec(t_sgmt *box, int neg, char *str, int lennbr)
{
	int		len;
	char	*res;
	char	*wid;

	res = NULL;
	len = (FLAGS->prec <= lennbr) ? 0 : (FLAGS->prec - lennbr);
	len += ((FLAGS->space && !neg) ? 1 : 0);
	wid = ft_putstrchar(len, '0');
	if (FLAGS->space && !neg)
		wid[0] = ' ';
	if (neg || FLAGS->plus)
	{
		if (neg)
			res = ft_strdup("-");
		else if (FLAGS->plus)
			res = ft_strdup("+");
		res = ft_conncat(res, wid, 1, len);
		free(wid);
		return (ft_conncat(res, str, ft_strlen(res), lennbr));
	}
	if (wid)
		res = ft_conncat(wid, str, len, lennbr);
	else
		return (ft_strdup(str));
	return (res);
}

char	*ft_printf_d_wid_neg(t_sgmt *box, int neg, char *str, int lennbr)
{
	int		len;
	char	*res;
	char	*wid;

	FLAGS->wid *= -1;
	if (neg)
		res = ft_conncat(ft_strdup("-"), str, 1, lennbr);
	else if (FLAGS->plus)
		res = ft_conncat(ft_strdup("+"), str, 1, lennbr);
	else
		res = ft_strdup(str);
	len = (FLAGS->wid <= lennbr ? 0 : FLAGS->wid - (lennbr + FLAGS->plus));
	wid = ft_putstrchar(len, ' ');
	res = ft_conncat(res, wid, ft_strlen(res), len);
	free(wid);
	return (res);
}

char	*ft_printf_d_wid(t_sgmt *box, int neg, char *str, int lennbr)
{
	int		len;
	char	c;
	char	*wid;
	char	*res;

	res = NULL;
	c = ' ';
	if (FLAGS->zero)
		c = (FLAGS->space && FLAGS->dot) ? ' ' : '0';
	if (neg)
		res = ft_strdup("-");
	else if (FLAGS->plus && (res = ft_strdup("+")))
		lennbr++;
	len = (FLAGS->wid <= lennbr) ? 0 : (FLAGS->wid - lennbr);
	wid = ft_putstrchar(len, c);
	if (FLAGS->space & FLAGS->zero)
		wid[0] = ' ';
	str = (str[0] == '0' && FLAGS->dot) ? (" ") : (str);
	if (c == ' ' && res)
		res = ft_conncat(wid, res, len, 1);
	else if (c == '0' && res && (res = ft_conncat(res, wid, 1, len)))
		free(wid);
	else if (res == NULL)
		return (ft_conncat(wid, str, ft_strlen(wid), lennbr));
	return (ft_conncat(res, str, ft_strlen(res), lennbr));
}
