/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putstrchar.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: quruiz <quruiz@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/24 14:12:21 by quruiz       #+#   ##    ##    #+#       */
/*   Updated: 2018/03/16 17:03:54 by quruiz      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_putstrchar(int nb, int c)
{
	char *str;

	if (nb <= 0)
		return (ft_strdup("\0"));
	str = (char *)malloc(sizeof(char) * nb + 1);
	ft_memset(str, c, nb);
	str[nb] = '\0';
	return (str);
}
