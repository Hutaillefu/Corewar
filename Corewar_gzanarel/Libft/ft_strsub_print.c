/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strsub_print.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/23 14:25:34 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/05 10:44:59 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/ft_printf.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*dest;
	unsigned int	i;

	i = 0;
	if (s != NULL)
	{
		if (len == 0 || start > ft_strlen((char *)s))
			dest = NULL;
		dest = (char *)malloc(sizeof(char) * len + 1);
		if (dest != NULL)
		{
			while (i < len)
			{
				dest[i] = s[start];
				start++;
				i++;
			}
			dest[i] = '\0';
		}
		return (dest);
	}
	return ((char *)s);
}
