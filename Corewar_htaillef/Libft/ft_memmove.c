/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memmove.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/23 14:17:12 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/11 15:38:13 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char				*dest;
	char				*s;

	dest = (char *)dst;
	s = (char *)src;
	if (s < dest)
		while (len--)
			dest[len] = s[len];
	else
		ft_memcpy(dest, s, len);
	return (dst);
}
