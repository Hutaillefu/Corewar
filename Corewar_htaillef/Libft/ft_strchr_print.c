/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strchr_print.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/23 14:20:00 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/05 10:45:17 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/ft_printf.h"

char	*ft_strchr(const char *s, int c)
{
	char			*str;
	unsigned char	l;

	str = (char *)s;
	l = (unsigned char)c;
	while (*str != l)
	{
		if (*str == '\0')
			return (NULL);
		str++;
	}
	return (str);
}
