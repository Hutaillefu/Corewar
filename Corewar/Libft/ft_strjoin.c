/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strjoin.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/23 14:22:17 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/11 15:48:48 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*dest;
	unsigned int	i;
	unsigned int	j;
	unsigned int	len1;
	unsigned int	len2;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len1 = ft_strlen((char *)s1);
	len2 = ft_strlen((char *)s2);
	dest = (char *)malloc(sizeof(*dest) * (len1 + len2 + 1));
	if (dest != NULL)
	{
		while (i < len1)
		{
			dest[i] = s1[i];
			i++;
		}
		j = 0;
		while (j < len2)
			dest[i++] = s2[j++];
		dest[i] = '\0';
	}
	return (dest);
}
