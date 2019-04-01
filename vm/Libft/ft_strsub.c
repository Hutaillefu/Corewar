/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strsub.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/23 14:25:34 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/15 15:40:35 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*dest;
	unsigned int	i;

	i = 0;
	if (s != NULL)
	{
		dest = NULL;
		dest = malloc(sizeof(char) * (len + 1));
		if (dest != NULL)
		{
			while (i < len)
			{
				dest[i] = s[start];
				start++;
				i++;
			}
			dest[i] = '\0';
			return (dest);
		}
	}
	return ((char *)s);
}
