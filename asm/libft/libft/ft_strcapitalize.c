/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strcapitalize.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: quruiz <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/05 18:21:09 by quruiz       #+#   ##    ##    #+#       */
/*   Updated: 2017/12/05 18:21:09 by quruiz      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcapitalize(char *str)
{
	int i;

	ft_strlowcase(str);
	i = 0;
	while (str[i])
	{
		if ((str[i] >= 'a' && str[i] <= 'z') && i == 0)
		{
			str[i] -= 32;
			i++;
		}
		else if ((str[i] >= 'a' && str[i] <= 'z') && i > 0 &&
				(str[i - 1] < '0' || str[i - 1] > '9'))
		{
			str[i] -= 32;
			i++;
		}
		while (str[i] >= 'a' && str[i] <= 'z' && str[i] != '\0')
			i++;
		i++;
	}
	return (str);
}
