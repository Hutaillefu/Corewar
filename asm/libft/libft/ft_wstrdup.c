/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_wstrdup.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: quruiz <quruiz@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/06 17:12:16 by quruiz       #+#   ##    ##    #+#       */
/*   Updated: 2018/04/07 17:09:49 by quruiz      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

wchar_t		*ft_wstrdup(wchar_t *str)
{
	wchar_t		*new_str;
	int			i;

	if (!str)
		return (NULL);
	i = 0;
	new_str = (wchar_t *)malloc(sizeof(wchar_t) * ft_wstrlen(str) + 1);
	if (!new_str)
		return (0);
	while (str[i] != '\0')
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
