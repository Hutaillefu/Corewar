/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memccpy.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/23 14:15:55 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/11 15:37:53 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned int	i;
	unsigned char	*dest;
	unsigned char	*s;
	unsigned char	x;

	i = 0;
	s = (unsigned char *)src;
	dest = (unsigned char *)dst;
	x = (unsigned char)c;
	while (i < n)
	{
		dest[i] = s[i];
		if (s[i] == x)
			return (dst + i + 1);
		i++;
	}
	return (NULL);
}
