/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf_x_justify.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: quruiz <quruiz@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/18 20:05:25 by quruiz       #+#   ##    ##    #+#       */
/*   Updated: 2018/04/07 20:36:58 by quruiz      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_printf_x_prec(t_sgmt *box, char *str, int lennbr)
{
	int		len;
	char	*res;
	char	*tmp;
	char	c;

	c = '0';
	len = (FLAGS->prec <= lennbr) ? 0 : (FLAGS->prec - lennbr);
	res = ft_conncat(ft_putstrchar(len, c), str, len, ft_strlen(str));
	if (FLAGS->sharp)
	{
		tmp = res;
		res = ft_conncat(ft_strdup("0x"), res, 2, ft_strlen(res));
		free(tmp);
	}
	return (res);
}

char	*ft_printf_x_pos(t_sgmt *box, char *str, int lennbr)
{
	int		lenspc;
	int		lenzero;
	char	*wid;
	char	*prec;
	char	*res;

	if (FLAGS->wid < FLAGS->prec)
		return (ft_printf_x_prec(box, str, lennbr - (FLAGS->sharp ? 2 : 0)));
	lenzero = (FLAGS->prec <= lennbr) ? 0 : (FLAGS->prec - lennbr);
	lennbr += (FLAGS->sharp ? 2 : 0);
	lenspc = FLAGS->wid - (lenzero + lennbr);
	wid = ft_putstrchar(lenspc, ' ');
	prec = ft_putstrchar(lenzero, '0');
	if (FLAGS->sharp)
	{
		res = ft_conncat(wid, "0x", ft_strlen(wid), 2);
		res = ft_conncat(res, prec, ft_strlen(res), ft_strlen(prec));
	}
	else
		res = ft_conncat(wid, prec, ft_strlen(wid), ft_strlen(prec));
	free(prec);
	res = ft_conncat(res, str, ft_strlen(res), lennbr);
	return (res);
}

char	*ft_printf_x_neg(t_sgmt *box, char *str, int lennbr)
{
	int		lenspc;
	int		lenzero;
	char	*wid;
	char	*tmp;
	char	*res;

	FLAGS->wid *= -1;
	if (FLAGS->wid < FLAGS->prec)
		return (ft_printf_x_prec(box, str, lennbr));
	lenzero = (FLAGS->prec <= lennbr) ? lennbr : (FLAGS->prec - lennbr);
	lennbr += (FLAGS->sharp ? 2 : 0);
	lenspc = FLAGS->wid - (lenzero + lennbr);
	res = ft_conncat(ft_putstrchar(lenzero, 48), str, lenzero, ft_strlen(str));
	if (FLAGS->sharp)
	{
		tmp = res;
		res = ft_conncat(ft_strdup("0x"), res, 2, ft_strlen(res));
		free(tmp);
	}
	wid = ft_putstrchar(lenspc, ' ');
	res = ft_conncat(res, wid, ft_strlen(res), lenspc);
	free(wid);
	return (res);
}

char	*ft_printf_x_wid_neg(t_sgmt *box, char *str, int lennbr)
{
	int		len;
	char	*prefix;
	char	*res;
	char	*wid;

	FLAGS->wid *= -1;
	if (FLAGS->sharp)
		prefix = ft_strdup("0x");
	else
		prefix = ft_strnew(0);
	len = (FLAGS->wid - lennbr);
	res = ft_conncat(prefix, str, ft_strlen(prefix), lennbr);
	if (len > 0)
	{
		wid = ft_putstrchar(len, ' ');
		res = ft_conncat(res, wid, ft_strlen(res), len);
		free(wid);
	}
	return (res);
}

char	*ft_printf_x_wid(t_sgmt *box, char *str, int lennbr)
{
	int		len;
	char	c;
	char	*res;
	char	*prefx;
	char	*wid;

	c = ((FLAGS->zero && !FLAGS->dot) ? '0' : ' ');
	if (FLAGS->sharp)
		prefx = ft_strdup("0x");
	else
		prefx = ft_strnew(0);
	if (FLAGS->wid > 0)
	{
		len = (FLAGS->wid <= lennbr) ? 0 : (FLAGS->wid - lennbr);
		wid = ft_putstrchar(len, c);
		if (c == ' ' && (res = ft_conncat(wid, prefx, len, ft_strlen(prefx))))
			free(prefx);
		if (c == '0' && (res = ft_conncat(prefx, wid, ft_strlen(prefx), len)))
			free(wid);
		res = ft_conncat(res, str, ft_strlen(res), lennbr);
	}
	else
		return (ft_printf_x_wid_neg(box, str, lennbr));
	return (res);
}
