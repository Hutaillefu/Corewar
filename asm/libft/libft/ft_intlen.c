/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_intlen.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: quruiz <quruiz@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/05 18:21:01 by quruiz       #+#   ##    ##    #+#       */
/*   Updated: 2018/10/17 20:41:20 by quruiz      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		ft_intlen(intmax_t nb)
{
	intmax_t	nbr;
	int			neg;
	int			len;

	len = 0;
	neg = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		if (nb == (-9223372036854775807) - 1)
			return (20);
		neg = 1;
		nbr = nb * -1;
	}
	else
		nbr = nb;
	while (nbr)
	{
		len++;
		nbr = nbr / 10;
	}
	len = len + neg;
	return (len);
}
