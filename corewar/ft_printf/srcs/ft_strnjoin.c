/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strnjoin.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: htaillef <htaillef@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/12 17:18:54 by htaillef     #+#   ##    ##    #+#       */
/*   Updated: 2018/02/15 12:22:07 by htaillef    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strnjoin(char *s1, char const *s2, size_t n)
{
	size_t	s1len;
	size_t	s2len;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	if (n > s2len)
		return (NULL);
	str = (char *)ft_memalloc(s1len + n + 1);
	if (!str)
		return (NULL);
	ft_strcat(str, s1);
	ft_strncat(str, s2, n);
	ft_memdel((void **)&s1);
	return (str);
}
