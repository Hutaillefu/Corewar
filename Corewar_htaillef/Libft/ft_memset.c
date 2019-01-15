/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memset.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/23 14:17:26 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/11 15:38:18 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char *str;

	str = (unsigned char *)b;
	if (len == 0)
		return (b);
	while (len--)
	{
		*str = (unsigned char)c;
		str++;
	}
	return ((unsigned char *)b);
}
