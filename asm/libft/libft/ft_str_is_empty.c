/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_str_is_empty.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: quruiz <quruiz@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/16 18:20:28 by quruiz       #+#   ##    ##    #+#       */
/*   Updated: 2019/03/16 19:03:22 by quruiz      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		ft_str_is_empty(char *str)
{
	int		i;
	int		res;

	i = 0;
	res = 0;
	if (!str)
		return (1);
	if (!ft_strlen(str))
		return (1);
	while (str[i])
	{
		res += ft_isprint(str[i]);
		i++;
	}
	if (!res)
		return (1);
	return (0);
}
