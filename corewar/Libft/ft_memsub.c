/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memncpy.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/15 12:21:27 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/15 13:20:27 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memsub(void *dst, const void *src, int start, size_t n)
{
	unsigned int		i;
	char				*dest;
	char				*sorc;

	i = 0;
	sorc = (char *)src;
	dest = (char *)dst;
	while (i < n)
	{
		dest[start] = sorc[i];
		i++;
		start++;
	}
	return (dst);
}