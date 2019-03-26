/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_check_limit.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: quruiz <quruiz@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/17 00:08:17 by quruiz       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/26 13:19:04 by quruiz      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		ft_check_limit(char *nb, char *limit)
{
	int		len_nb;
	int		len_limit;
	int		i;

	len_nb = ft_strlen(nb);
	len_limit = ft_strlen(limit);
	i = 0;
	if (!ft_str_is_numeric(nb))
		return (0);
	if (len_nb < len_limit)
		return (1);
	else if (len_nb == len_limit)
	{
		while (i < len_nb)
		{
			if ((nb[i] - 48) == (limit[i] - 48))
				i++;
			else
				return (((nb[i] - 48) < (limit[i] - 48)) ? 1 : 0);
		}
		return (1);
	}
	return (0);
}
