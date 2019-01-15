/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strchr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/23 14:20:00 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/11 15:38:56 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"

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
