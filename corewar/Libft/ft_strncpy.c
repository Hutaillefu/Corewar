/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strncpy.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/23 14:23:43 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/11 15:39:56 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	unsigned int	i;
	unsigned int	j;
	char			*str;

	str = (char *)src;
	j = ft_strlen(str);
	i = 0;
	while (src[i] != '\0' && (i < len))
	{
		dst[i] = src[i];
		i++;
	}
	if (j < len)
		while (j < len)
		{
			dst[i] = '\0';
			i++;
			j++;
		}
	return (dst);
}
