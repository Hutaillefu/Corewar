/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf_c.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: quruiz <quruiz@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/12 16:17:18 by quruiz       #+#   ##    ##    #+#       */
/*   Updated: 2018/04/05 18:01:34 by quruiz      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_printf_lc_justify(t_sgmt *box, int len, char *s)
{
	char	*wid;
	char	*res;

	if (FLAGS->wid > 0)
	{
		wid = ft_putstrchar((FLAGS->wid) - len, ' ');
		res = ft_conncat(wid, s, ft_strlen(wid), len);
		free(s);
	}
	else
	{
		FLAGS->wid *= -1;
		box->c = box->c ? -1 : 0;
		wid = ft_putstrchar((FLAGS->wid) - len, ' ');
		res = ft_conncat(s, wid, len, ft_strlen(wid));
		free(wid);
	}
	return (res);
}

char	*ft_printf_lc(t_sgmt *box, va_list arg)
{
	wint_t	c;
	int		len;
	char	*s;

	c = va_arg(arg, wint_t);
	len = ft_wcharlen(c);
	if (c == 0)
		box->c = 1;
	if (len > MB_CUR_MAX || c < 0 || len == -1)
	{
		box->err = -1;
		return (NULL);
	}
	if (len == 1)
		c = (char)c;
	s = ft_wcharstr(c, len);
	if (FLAGS->wid != 0)
		return (ft_printf_lc_justify(box, len, s));
	return (s);
}

char	*ft_printf_c_wid(t_sgmt *box, char *s)
{
	char	*wid;
	char	*res;
	char	c;

	c = ' ';
	if (FLAGS->zero)
		c = (FLAGS->space) ? ' ' : '0';
	if (FLAGS->wid > 0)
	{
		wid = ft_putstrchar((FLAGS->wid) - 1, c);
		res = ft_conncat(wid, s, ft_strlen(wid), 1);
	}
	else
	{
		FLAGS->wid *= -1;
		box->c = box->c ? -1 : 0;
		wid = ft_putstrchar((FLAGS->wid) - 1, c);
		res = ft_conncat(s, wid, ft_strlen(s), ft_strlen(wid));
		free(wid);
	}
	return (res);
}

char	*ft_printf_c(t_sgmt *box, va_list arg)
{
	char	c;
	char	*str;

	if (FLAGS->l == 1)
		return (ft_printf_lc(box, arg));
	c = va_arg(arg, int);
	if (c == 0)
		box->c = 1;
	str = ft_strnew(1);
	str[0] = c;
	if (FLAGS->wid != 0)
		return (ft_printf_c_wid(box, str));
	return (str);
}

char	*ft_printf_percent(t_sgmt *box)
{
	char	*res;
	char	*wid;
	char	c;
	int		nb;

	c = ' ';
	if (FLAGS->zero)
		c = (FLAGS->space) ? ' ' : '0';
	if (FLAGS->wid != 0)
	{
		nb = FLAGS->wid - 1;
		if (FLAGS->wid > 0)
			res = ft_conncat(ft_putstrchar(nb, c), "%", nb, 1);
		else
		{
			FLAGS->wid *= -1;
			wid = ft_putstrchar(FLAGS->wid - 1, ' ');
			res = ft_conncat(ft_strdup("%"), wid, 1, FLAGS->wid - 1);
			free(wid);
		}
	}
	else
		res = ft_strdup("%");
	return (res);
}
