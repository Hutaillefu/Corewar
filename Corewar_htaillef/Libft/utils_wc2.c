/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils_wc2.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/06 13:24:59 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/05 10:44:44 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/ft_printf.h"

int		ft_wclen(wchar_t c)
{
	if (MB_CUR_MAX == 1 && (c >= 128 && c <= 255))
		return (1);
	else if (c < 128)
		return (1);
	else if (c >= 128 && c <= 2047)
		return (2);
	else if (c >= 2048 && c <= 65535)
		return (3);
	else if (c >= 65536 && c <= 1114111)
		return (4);
	else
		return (0);
}

int		ft_wstrlen(wchar_t *wstr)
{
	int i;
	int len;

	i = -1;
	len = 0;
	while (wstr[++i])
		len += ft_wclen(wstr[i]);
	return (len);
}

int		ft_check_wchar(wchar_t c)
{
	if (MB_CUR_MAX == 1 && c >= 256)
		return (-1);
	if (MB_CUR_MAX == 4 && (c >= 55296 && c <= 57343))
		return (-1);
	if (c < 0)
		return (-1);
	if (c > 1114111)
		return (-1);
	else
		return (1);
}
