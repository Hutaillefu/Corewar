/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils_w.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/31 16:48:56 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/05 10:44:49 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/ft_printf.h"

char	*ft_putchar_to_char(wchar_t c)
{
	char	*str;
	int		i;

	i = 0;
	if (!(str = malloc(sizeof(char) * ft_wclen(c) + 1)))
		return (NULL);
	if (c <= 0xFF && MB_CUR_MAX == 1)
	{
		str[i++] = c;
		str[i++] = '\0';
	}
	else if (c <= 0x7F)
	{
		str[i++] = c;
		str[i++] = '\0';
	}
	else if (c <= 0x7FF)
	{
		str[i++] = (c >> 6) + 0xC0;
		str[i++] = (c & 0x3F) + 0x80;
		str[i++] = '\0';
	}
	else
		ft_putchar_to_char_2(c, str, i);
	return (str);
}

char	*ft_putchar_to_char_2(wchar_t c, char *str, int i)
{
	if (c <= 0xFFFF)
	{
		str[i++] = (c >> 12) + 0xe0;
		str[i++] = ((c >> 6) & 0x3f) + 0x80;
		str[i++] = (c & 0x3f) + 0x80;
		str[i++] = '\0';
	}
	else if (c <= 0x10FFFF)
	{
		str[i++] = (c >> 18) + 0xf0;
		str[i++] = ((c >> 12) & 0x3f) + 0x80;
		str[i++] = ((c >> 6) & 0x3f) + 0x80;
		str[i++] = (c & 0x3f) + 0x80;
		str[i++] = '\0';
	}
	return (str);
}

int		ft_putwchar_to_char(wchar_t c, char *str, int i)
{
	int len;

	if (ft_check_wchar(c) == -1)
		return (-1);
	len = ft_wclen(c);
	if (len == 1)
		str[i++] = c;
	else if (len == 2)
	{
		str[i++] = (c >> 6) + 0xC0;
		str[i++] = (c & 0x3F) + 0x80;
	}
	else
		i = ft_putwchar_to_char_2(c, str, i, len);
	return (i);
}

int		ft_putwchar_to_char_2(wchar_t c, char *str, int i, int len)
{
	if (len == 3)
	{
		str[i++] = (c >> 12) + 0xe0;
		str[i++] = ((c >> 6) & 0x3f) + 0x80;
		str[i++] = (c & 0x3f) + 0x80;
	}
	else if (len == 4)
	{
		str[i++] = (c >> 18) + 0xf0;
		str[i++] = ((c >> 12) & 0x3f) + 0x80;
		str[i++] = ((c >> 6) & 0x3f) + 0x80;
		str[i++] = (c & 0x3f) + 0x80;
	}
	return (i);
}
