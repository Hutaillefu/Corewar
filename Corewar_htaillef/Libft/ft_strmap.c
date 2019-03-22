/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strmap.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/23 14:22:58 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/11 15:50:15 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		i;
	char	*dst;
	int		len;

	len = ft_strlen1((char *)s);
	i = 0;
	if (s != NULL)
	{
		if (len == 0)
			dst = NULL;
		dst = (char *)malloc(sizeof(char) * (len + 1));
		if (dst != NULL)
		{
			while (s[i])
			{
				dst[i] = f(s[i]);
				i++;
			}
			dst[i] = '\0';
		}
		return (dst);
	}
	return ((char *)s);
}
