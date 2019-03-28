/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf_p.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: quruiz <quruiz@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/26 16:08:30 by quruiz       #+#   ##    ##    #+#       */
/*   Updated: 2018/04/07 20:13:09 by quruiz      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_printf_p_prec(t_sgmt *box, char *str, int lennbr)
{
	int		len;
	char	*res;
	char	*tmp;

	len = (FLAGS->prec <= lennbr) ? 0 : (FLAGS->prec - lennbr);
	tmp = ft_putstrchar(len, '0');
	res = ft_conncat(ft_strdup("0x"), tmp, 2, len);
	res = ft_conncat(res, str, ft_strlen(res), lennbr);
	free(tmp);
	return (res);
}

char	*ft_printf_p_pos(t_sgmt *box, char *str, int lennbr)
{
	int		len;
	char	*wid;
	char	*prec;
	char	*res;

	if (FLAGS->wid < FLAGS->prec)
		return (ft_printf_p_prec(box, str, lennbr - 2));
	len = (FLAGS->prec <= lennbr) ? 0 : (FLAGS->prec - lennbr);
	prec = ft_putstrchar(len, '0');
	len = FLAGS->wid - (len + lennbr);
	wid = ft_putstrchar(len, ' ');
	if (*prec != '\0' || *wid != '\0')
	{
		res = ft_conncat(wid, "0x", ft_strlen(wid), 2);
		res = ft_conncat(res, prec, ft_strlen(res), ft_strlen(prec));
		free(prec);
	}
	else
		res = ft_strdup("\0");
	res = ft_conncat(res, str, ft_strlen(res), lennbr);
	return (res);
}

char	*ft_printf_p_neg(t_sgmt *box, char *str, int lennbr)
{
	int		lenspc;
	int		lenzero;
	char	*wid;
	char	*prec;
	char	*res;

	FLAGS->wid *= -1;
	if (FLAGS->wid < FLAGS->prec)
		return (ft_printf_x_prec(box, str, lennbr));
	lenspc = FLAGS->wid - FLAGS->prec;
	lenzero = (FLAGS->prec <= lennbr) ? lennbr : (FLAGS->prec - lennbr);
	prec = ft_putstrchar(lenzero, '0');
	prec = ft_conncat(ft_strdup("0x"), prec, 2, lenzero);
	res = ft_conncat(prec, str, ft_strlen(prec), lennbr);
	wid = ft_putstrchar(lenspc, ' ');
	res = ft_conncat(res, wid, ft_strlen(res), lenspc);
	free(wid);
	return (res);
}

char	*ft_printf_p_wid_neg(t_sgmt *box, char *str, int lennbr)
{
	char	*wid;
	char	*prefix;
	char	*res;
	char	c;
	int		len;

	prefix = ft_strdup("0x");
	c = (FLAGS->zero ? '0' : ' ');
	FLAGS->wid *= -1;
	len = (FLAGS->wid <= lennbr) ? 0 : (FLAGS->wid - lennbr);
	res = ft_conncat(prefix, str, 2, lennbr);
	wid = ft_putstrchar(len, c);
	res = ft_conncat(res, wid, ft_strlen(res), len);
	free(wid);
	return (res);
}

char	*ft_printf_p_wid(t_sgmt *box, char *str, int lennbr)
{
	int		len;
	char	*res;
	char	*prefix;
	char	*wid;
	char	c;

	prefix = ft_strdup("0x");
	c = (FLAGS->zero ? '0' : ' ');
	if (FLAGS->wid > 0)
	{
		len = (FLAGS->wid <= lennbr) ? 0 : (FLAGS->wid - lennbr);
		wid = ft_putstrchar(len, c);
		if (c == ' ' && (res = ft_conncat(wid, prefix, len, 2)))
			free(prefix);
		else if ((res = ft_conncat(prefix, wid, 2, len)))
			free(wid);
		res = ft_conncat(res, str, ft_strlen(res), lennbr);
	}
	else
		res = ft_printf_p_wid_neg(box, str, lennbr);
	return (res);
}
