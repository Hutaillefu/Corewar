/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strncat.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: quruiz <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/05 18:21:12 by quruiz       #+#   ##    ##    #+#       */
/*   Updated: 2017/12/05 18:21:12 by quruiz      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	j;
	char	*str1;
	char	*str2;

	i = 0;
	j = 0;
	str1 = (char *)s1;
	str2 = (char *)s2;
	while (str1[j])
		j++;
	while (str2[i] != '\0' && i < n)
	{
		str1[j] = str2[i];
		i++;
		j++;
	}
	str1[j] = '\0';
	return ((char *)str1);
}
