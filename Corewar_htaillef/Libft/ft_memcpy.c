/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memcpy.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/23 14:16:40 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/11 15:38:05 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned int		i;
	char				*dest;
	char				*sorc;

	i = 0;
	sorc = (char *)src;
	dest = (char *)dst;
	while (i < n)
	{
		dest[i] = sorc[i];
		i++;
	}
	return (dst);
}
