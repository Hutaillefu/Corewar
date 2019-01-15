/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memchr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/23 14:16:10 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/11 15:37:57 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	l;
	int				i;

	i = 0;
	str = (unsigned char *)s;
	l = (unsigned char)c;
	while (n--)
	{
		if (str[i] == l)
			return (&(str[i]));
		i++;
	}
	return (NULL);
}
