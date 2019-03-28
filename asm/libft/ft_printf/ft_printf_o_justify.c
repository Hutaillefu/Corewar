/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf_o_justify.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: quruiz <quruiz@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/24 22:59:10 by quruiz       #+#   ##    ##    #+#       */
/*   Updated: 2018/04/04 03:05:20 by quruiz      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_printf_o_prec(t_sgmt *box, char *str, int lennbr)
{
	int		len;
	char	*res;
	char	*prec;
	char	c;

	c = '0';
	len = (FLAGS->prec <= lennbr) ? 0 : (FLAGS->prec - lennbr);
	if (FLAGS->sharp && !len && *str != '0')
		res = ft_conncat(ft_strdup("0"), str, 1, lennbr);
	else
	{
		prec = ft_putstrchar(len, c);
		res = ft_conncat(prec, str, len, lennbr);
	}
	return (res);
}

char	*ft_printf_o_pos(t_sgmt *box, char *str, int lennbr)
{
	int		lenspc;
	int		lenzero;
	char	*wid;
	char	*prec;
	char	*res;

	if (FLAGS->wid < FLAGS->prec)
		return (ft_printf_o_prec(box, str, lennbr));
	lenzero = (FLAGS->prec <= lennbr) ? 0 : (FLAGS->prec - lennbr);
	lenspc = FLAGS->wid - (lenzero + lennbr);
	wid = ft_putstrchar(lenspc, ' ');
	prec = ft_putstrchar(lenzero, '0');
	res = ft_strdup(str);
	if (*prec != '\0' || *wid != '\0')
	{
		res = ft_conncat(wid, prec, lenspc, lenzero);
		free(prec);
	}
	else
		res = ft_strdup("\0");
	res = ft_conncat(res, str, ft_strlen(res), lennbr);
	return (res);
}

char	*ft_printf_o_neg(t_sgmt *box, char *str, int lennbr)
{
	int		lenspc;
	int		lenzero;
	char	*wid;
	char	*prec;
	char	*res;

	FLAGS->wid *= -1;
	if (FLAGS->wid < FLAGS->prec)
		return (ft_printf_o_prec(box, str, lennbr));
	lenspc = FLAGS->wid - FLAGS->prec;
	lenzero = (FLAGS->prec <= lennbr) ? 0 : (FLAGS->prec - lennbr);
	prec = ft_putstrchar(lenzero, '0');
	res = ft_conncat(prec, str, lenzero, lennbr);
	wid = ft_putstrchar(lenspc, ' ');
	res = ft_conncat(res, wid, ft_strlen(res), lenspc);
	free(wid);
	return (res);
}

char	*ft_printf_o_wid_neg(t_sgmt *box, char *str, int lennbr)
{
	int		len;
	char	*wid;
	char	*res;

	FLAGS->wid *= -1;
	len = (FLAGS->wid - lennbr);
	wid = ft_putstrchar(len, ' ');
	if (FLAGS->sharp)
		res = ft_conncat(ft_strdup("0"), str, 1, lennbr);
	else
		res = ft_strdup(str);
	res = ft_conncat(res, wid, ft_strlen(res), ft_strlen(wid));
	return (res);
}

char	*ft_printf_o_wid(t_sgmt *box, char *str, int lennbr)
{
	int		len;
	char	c;
	char	*wid;
	char	*res;

	c = ' ';
	res = NULL;
	if (FLAGS->wid > 0 && FLAGS->prec == 0)
	{
		len = (FLAGS->wid <= lennbr) ? 0 : (FLAGS->wid - lennbr);
		c = (FLAGS->zero && !FLAGS->dot) ? ('0') : (' ');
		wid = ft_putstrchar(len, c);
		if (FLAGS->sharp)
			res = ft_conncat(wid, "0", len, 1);
		else
		{
			res = ft_strdup(wid);
			free(wid);
		}
		len = ft_strlen(res);
		res = ft_conncat(res, str, len, lennbr);
	}
	else if (FLAGS->wid < 0 && FLAGS->prec == 0)
		res = ft_printf_o_wid_neg(box, str, lennbr);
	return (res);
}
