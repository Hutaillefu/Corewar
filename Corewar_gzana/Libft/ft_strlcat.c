/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strlcat.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/23 14:22:27 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/11 15:39:35 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int i;
	unsigned int j;

	i = 0;
	while (dst[i] && i < size)
		i++;
	j = i;
	if (size == 0)
		return (i + ft_strlen((char *)src));
	while (src[i - j] && i < (size - 1))
	{
		if (size != 1)
		{
			dst[i] = src[i - j];
			i++;
		}
		i++;
	}
	dst[i] = '\0';
	return (j + ft_strlen((char *)src));
}
