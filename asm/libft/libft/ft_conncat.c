/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_conncat.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: quruiz <quruiz@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/28 17:55:16 by quruiz       #+#   ##    ##    #+#       */
/*   Updated: 2018/03/12 07:34:36 by quruiz      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_conncat(char *res, const char *src, size_t l1, size_t l2)
{
	char	*toret;
	size_t	size;

	size = l1 + l2;
	toret = ft_strnew(size);
	if (!toret)
		return (NULL);
	if (res)
	{
		ft_strncpy(toret, res, l1);
		free(res);
	}
	ft_strncpy(toret + l1, src, l2);
	return (toret);
}
