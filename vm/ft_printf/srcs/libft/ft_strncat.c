/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strncat.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: htaillef <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/30 14:11:24 by htaillef     #+#   ##    ##    #+#       */
/*   Updated: 2017/11/30 14:11:25 by htaillef    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strncat(char *dst, const char *src, size_t n)
{
	size_t	i;
	size_t	y;

	y = ft_strlen(dst);
	i = 0;
	while (i < n && src[i])
	{
		dst[y] = src[i];
		i++;
		y++;
	}
	dst[y] = '\0';
	return (dst);
}
