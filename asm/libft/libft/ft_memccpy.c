/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memccpy.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: quruiz <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/05 18:21:04 by quruiz       #+#   ##    ##    #+#       */
/*   Updated: 2017/12/05 18:21:04 by quruiz      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*tmpd;
	const unsigned char	*tmps;
	size_t				i;
	unsigned char		ltr;

	i = 0;
	tmpd = (unsigned char *)dst;
	tmps = (const unsigned char *)src;
	ltr = (unsigned char)c;
	while (i < n)
	{
		tmpd[i] = tmps[i];
		if (tmpd[i] == ltr)
		{
			i++;
			return ((unsigned char *)(tmpd + i));
		}
		i++;
	}
	return (NULL);
}
