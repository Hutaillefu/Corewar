/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   string_process.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: htaillef <htaillef@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/06 19:35:21 by htaillef     #+#   ##    ##    #+#       */
/*   Updated: 2018/02/20 17:01:57 by htaillef    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

char		*process_string(void *value)
{
	char *res;

	res = (char *)value;
	if (!res)
		return (ft_strdup("(null)"));
	res = ft_strdup(res);
	return (res);
}

char		*process_char(void *value)
{
	char *res;

	if ((unsigned char)value == 0)
		res = ft_strdup("^@");
	else
	{
		res = ft_memalloc(2);
		res[0] = (unsigned char)value;
		res[1] = '\0';
	}
	return (res);
}

static char	*process_wchar_real(wchar_t c)
{
	char *res;

	if (c == 0)
		res = ft_strdup("^@");
	else
		res = wchartostr(c);
	return (res);
}

char		*process_wchar(void *value)
{
	wchar_t	c;

	c = (wchar_t)value;
	if (c >= 0 && c <= 255)
		return (process_char(value));
	return (process_wchar_real(c));
}

char		*process_wstr(void *value)
{
	wchar_t *wstr;
	char	*res;
	char	*ret;
	char	*wchar;

	wstr = (wchar_t *)value;
	if (!wstr)
		return (ft_strdup("(null)"));
	res = ft_strdup("");
	while (*wstr)
	{
		ret = res;
		wchar = process_wchar_real(*wstr);
		res = ft_strjoin(res, wchar);
		ft_memdel((void **)&ret);
		ft_memdel((void **)&wchar);
		wstr++;
	}
	return (res);
}
