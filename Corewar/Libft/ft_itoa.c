/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_itoa.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/23 14:13:32 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/11 15:55:32 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_itoa(int n)
{
	int		len;
	char	*str;
	int		limit;
	long	nb;

	nb = (long)n;
	limit = 0;
	len = ft_nbrlen(nb);
	str = (char *)malloc(sizeof(char) * len + 1);
	if (str == NULL)
		return (NULL);
	str[len] = '\0';
	if (nb < 0)
	{
		str[0] = '-';
		limit = 1;
		nb = -nb;
	}
	while (--len >= limit)
	{
		str[len] = (nb % 10) + 48;
		nb = nb / 10;
	}
	return (str);
}
