/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strsub.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: quruiz <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/05 18:21:14 by quruiz       #+#   ##    ##    #+#       */
/*   Updated: 2017/12/05 18:21:14 by quruiz      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str_tmp;
	size_t	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (!(str_tmp = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (i < len)
	{
		str_tmp[i] = s[start + i];
		i++;
	}
	str_tmp[i] = '\0';
	return (str_tmp);
}
