/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_itoa_base.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: quruiz <quruiz@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/19 14:40:15 by quruiz       #+#   ##    ##    #+#       */
/*   Updated: 2018/03/16 15:51:11 by quruiz      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_itoa_len(uintmax_t nb, int base)
{
	unsigned int p;

	p = 1;
	while ((nb) && (nb /= base))
		p++;
	return (p);
}

char			*ft_itoa_base(uintmax_t nb, int b)
{
	char	*str;
	int		i;

	i = 0;
	if (!nb)
		str = ft_strdup("0");
	else
	{
		str = (malloc(sizeof(char) * ft_itoa_len(nb, b)));
		ft_bzero(str, ft_strlen(str));
		while (nb)
		{
			str[i] = ((nb % b) > 9) ? ((nb % b - 10) + 'a') : ((nb % b) + 48);
			nb = nb / b;
			i++;
		}
		str[i] = '\0';
		ft_strrev(str);
	}
	return (str);
}
