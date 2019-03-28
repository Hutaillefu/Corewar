/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_utils.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: quruiz <quruiz@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/06 17:05:32 by quruiz       #+#   ##    ##    #+#       */
/*   Updated: 2018/04/05 22:01:07 by quruiz      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_itoa_pf(intmax_t n)
{
	char	*str;
	int		len;
	int		neg;

	neg = 0;
	len = ft_intlen(n);
	if (!(str = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	str[len] = '\0';
	if (n < 0)
	{
		neg = 1;
		n = n * -1;
	}
	if (n == (-9223372036854775807) - 1)
		return (ft_strdup("9223372036854775808"));
	while (len--)
	{
		str[len] = (n % 10) + 48;
		n = n / 10;
	}
	if (neg)
		str[0] = '-';
	return (str);
}

char	*ft_wcharstr(wchar_t c, int len)
{
	char	*str;

	str = ft_strnew(len + 1);
	if (c <= 0x7F)
		str[0] = c;
	else if (c <= 0x7FF)
	{
		str[0] = ((c >> 6) | 0xC0);
		str[1] = ((c & 0x3F) | 0x80);
	}
	else if (c <= 0xFFFF)
	{
		str[0] = ((c >> 12) | 0xE0);
		str[1] = (((c >> 6) & 0x3F) | 0x80);
		str[2] = ((c & 0x3F) | 0x80);
	}
	else if (c <= 0x10FFFF)
	{
		str[0] = ((c >> 18) | 0xF0);
		str[1] = (((c >> 12) & 0x3F) | 0x80);
		str[2] = (((c >> 6) & 0x3F) | 0x80);
		str[3] = ((c & 0x3F) | 0x80);
	}
	return (str);
}

char	*ft_wchar_to_char(wchar_t *s, char *res, int len)
{
	char	*tmp;

	tmp = ft_wcharstr(*s, len);
	if (!res)
		res = ft_strdup(tmp);
	else
		res = ft_conncat(res, tmp, ft_strlen(res), len);
	free(tmp);
	return (res);
}

void	ft_get_unsigned_arg(uintmax_t *tmp, t_sgmt *box, va_list arg)
{
	if (FLAGS->l == 1)
		*tmp = (unsigned long)va_arg(arg, unsigned long);
	else if (FLAGS->l == 2)
		*tmp = (unsigned long long)va_arg(arg, unsigned long long);
	else if (FLAGS->j)
		*tmp = (uintmax_t)va_arg(arg, uintmax_t);
	else if (FLAGS->z)
		*tmp = (size_t)va_arg(arg, size_t);
	else if (FLAGS->h == 1)
		*tmp = (unsigned short)va_arg(arg, unsigned int);
	else if (FLAGS->h == 2)
		*tmp = (unsigned char)va_arg(arg, unsigned int);
	else if (!(FLAGS->h && FLAGS->l && FLAGS->j && FLAGS->z))
		*tmp = (unsigned int)va_arg(arg, unsigned int);
	else
		return ;
}

void	ft_get_signed_arg(intmax_t *tmp, t_sgmt *box, va_list arg)
{
	if (FLAGS->l == 1)
		*tmp = (long)va_arg(arg, long);
	else if (FLAGS->l == 2)
		*tmp = (long long)va_arg(arg, long long);
	else if (FLAGS->j)
		*tmp = (intmax_t)va_arg(arg, intmax_t);
	else if (FLAGS->z)
		*tmp = (ssize_t)va_arg(arg, ssize_t);
	else if (FLAGS->h == 1)
		*tmp = (short)va_arg(arg, int);
	else if (FLAGS->h == 2)
		*tmp = (char)va_arg(arg, int);
	else if (!(FLAGS->h && FLAGS->l && FLAGS->j && FLAGS->z))
		*tmp = (int)va_arg(arg, int);
	else
		return ;
}
