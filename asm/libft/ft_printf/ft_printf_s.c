/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf_s.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: quruiz <quruiz@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/08 14:03:43 by quruiz       #+#   ##    ##    #+#       */
/*   Updated: 2018/04/07 20:24:05 by quruiz      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_wchartochar(wchar_t *s, t_sgmt *box)
{
	char	*res;
	int		len;
	int		prec;

	res = NULL;
	prec = FLAGS->prec;
	while (*s)
	{
		len = ft_wcharlen(*s);
		if (len > MB_CUR_MAX || len == -1)
		{
			box->err = -1;
			return (NULL);
		}
		*s = (MB_CUR_MAX == 1 && len == 1) ? (char)*s : *s;
		if (len <= prec || FLAGS->prec == 0)
		{
			res = ft_wchar_to_char(s, res, len);
			prec -= len;
			if (prec == 0 && FLAGS->prec != 0)
				break ;
		}
		s++;
	}
	return (res);
}

char	*ft_printf_ls_justify(char *s, int len, t_sgmt *box, char c)
{
	int		spc;
	int		neg;
	char	*wid;
	char	*res;

	neg = FLAGS->wid > 0 ? 0 : 1;
	FLAGS->wid *= neg ? -1 : 1;
	if (!len)
		spc = FLAGS->wid;
	else
		spc = FLAGS->wid - len;
	if (!neg)
	{
		res = ft_putstrchar(spc, c);
		res = ft_conncat(res, s, ft_strlen(res), len);
		free(s);
	}
	else
	{
		wid = ft_putstrchar(spc, c);
		res = ft_conncat(s, wid, ft_strlen(s), ft_strlen(wid));
		free(wid);
	}
	return (res);
}

char	*ft_printf_ls(t_sgmt *box, va_list arg, char c)
{
	int		len;
	char	*res;
	wchar_t	*s;

	len = 0;
	s = va_arg(arg, wchar_t *);
	if (s == NULL)
		s = ft_wstrdup(L"(null)");
	s = ft_wstrdup(s);
	if (FLAGS->dot && FLAGS->prec == 0)
	{
		free(s);
		return (ft_putstrchar(FLAGS->wid, c));
	}
	res = ft_wchartochar(s, box);
	len = ft_strlen(res);
	if (FLAGS->wid != 0 && (res || box->err == 0))
		res = ft_printf_ls_justify(res, len, box, c);
	free(s);
	return (res);
}

char	*ft_printf_s_justify(char *s, int len, t_sgmt *box, char c)
{
	int		neg;
	int		lenstr;
	char	*wid;
	char	*res;

	neg = FLAGS->wid > 0 ? 0 : 1;
	lenstr = (FLAGS->prec <= len && FLAGS->prec) ? FLAGS->prec : len;
	FLAGS->wid *= neg ? -1 : 1;
	if (!len)
		wid = ft_putstrchar(FLAGS->wid, c);
	else if (lenstr < FLAGS->wid)
		wid = ft_putstrchar(FLAGS->wid - lenstr, (neg ? ' ' : c));
	else
		wid = ft_strnew(0);
	if (FLAGS->wid && FLAGS->prec == 0 && FLAGS->dot)
		return (ft_putstrchar(FLAGS->wid, c));
	if (!neg)
		res = ft_conncat(wid, s, ft_strlen(wid), lenstr);
	else
	{
		res = ft_strsub(s, 0, !FLAGS->prec ? len : FLAGS->prec);
		res = ft_conncat(res, wid, ft_strlen(res), ft_strlen(wid));
		free(wid);
	}
	return (res);
}

char	*ft_printf_s(t_sgmt *box, va_list arg)
{
	char	*res;
	char	*s;
	char	c;

	c = ' ';
	if (FLAGS->zero)
		c = ((FLAGS->space) ? ' ' : '0');
	if (FLAGS->l == 1)
		res = ft_printf_ls(box, arg, c);
	else
	{
		s = va_arg(arg, char *);
		if (s == NULL && !FLAGS->zero)
			s = "(null)";
		s = ft_strdup(s);
		if (FLAGS->wid != 0)
			res = ft_printf_s_justify(s, ft_strlen(s), box, c);
		else if (FLAGS->prec >= 0 && FLAGS->dot)
			res = ft_strsub(s, 0, FLAGS->prec);
		else
			res = ft_strdup(s);
		free(s);
	}
	return (res);
}
