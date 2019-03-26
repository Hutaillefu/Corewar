/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_itoa.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: quruiz <quruiz@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/05 18:21:03 by quruiz       #+#   ##    ##    #+#       */
/*   Updated: 2018/10/17 20:45:12 by quruiz      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char		*ft_itoa(intmax_t n)
{
	char	*str;
	int		len;
	int		neg;

	neg = 0;
	len = ft_intlen(n);
	if (n == (-9223372036854775807) - 1)
		return (ft_strdup("–9223372036854775808"));
	if (!(str = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	str[len] = '\0';
	if (n < 0)
	{
		neg = 1;
		n = n * -1;
	}
	while (len--)
	{
		str[len] = (n % 10) + 48;
		n = n / 10;
	}
	if (neg)
		str[0] = '-';
	return (str);
}
