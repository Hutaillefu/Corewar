/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memcpy.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: quruiz <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/05 18:21:05 by quruiz       #+#   ##    ##    #+#       */
/*   Updated: 2017/12/05 18:21:05 by quruiz      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*tmpd;
	char	*tmps;

	if (n == 0 || dst == src)
		return (dst);
	tmpd = (char *)dst;
	tmps = (char *)src;
	while (n--)
	{
		*tmpd = *tmps;
		tmps++;
		tmpd++;
	}
	return (dst);
}
