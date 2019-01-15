/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strmapi.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/23 14:23:06 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/11 15:50:58 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*dest;
	int				len;

	len = ft_strlen((char *)s);
	i = 0;
	if (s != NULL)
	{
		if (len == 0)
			dest = NULL;
		dest = (char *)malloc(sizeof(char) * (len + 1));
		if (dest != NULL)
		{
			while (s[i])
			{
				dest[i] = f(i, s[i]);
				i++;
			}
			dest[i] = '\0';
		}
		return (dest);
	}
	return ((char *)s);
}
