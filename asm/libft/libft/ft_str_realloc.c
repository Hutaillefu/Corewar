/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_str_realloc.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: quruiz <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/05 18:21:08 by quruiz       #+#   ##    ##    #+#       */
/*   Updated: 2017/12/05 18:21:08 by quruiz      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_str_realloc(char *str, size_t size)
{
	char		*tmp;
	size_t		total_size;

	if (!str)
		return (NULL);
	if (size == 0)
		return (str);
	total_size = ft_strlen(str) + size;
	if (!(tmp = ft_memalloc(sizeof(char) * total_size)))
		return (NULL);
	ft_strcpy(tmp, str);
	return (tmp);
}
