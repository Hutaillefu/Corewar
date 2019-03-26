/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_uintlen.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: quruiz <quruiz@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/17 20:35:30 by quruiz       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/26 13:18:44 by quruiz      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		ft_uintlen(uintmax_t nb)
{
	uintmax_t	nbr;
	int			len;

	len = 0;
	if (nb == 0)
		return (1);
	else
		nbr = nb;
	while (nbr)
	{
		len++;
		nbr = nbr / 10;
	}
	return (len);
}
