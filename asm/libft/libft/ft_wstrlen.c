/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_wstrlen.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: quruiz <quruiz@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/06 17:14:43 by quruiz       #+#   ##    ##    #+#       */
/*   Updated: 2018/04/07 17:09:26 by quruiz      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_wstrlen(wchar_t const *str)
{
	size_t			len;
	wchar_t const	*s;

	len = 0;
	s = str;
	while (*s != '\0')
		s++;
	len = s - str;
	return (len);
}
