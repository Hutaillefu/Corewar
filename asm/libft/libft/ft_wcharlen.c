/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_wcharlen.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: quruiz <quruiz@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/23 16:28:08 by quruiz       #+#   ##    ##    #+#       */
/*   Updated: 2018/04/05 18:00:00 by quruiz      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		ft_wcharlen(wchar_t c)
{
	int		len;

	len = 0;
	if (c >= 0xD800 && c <= 0xDFFF)
		len = -1;
	else if (c <= 0x7F || (MB_CUR_MAX == 1 && c <= 0xFF))
		len = 1;
	else if (c <= 0x7FF)
		len = 2;
	else if (c <= 0xFFFF)
		len = 3;
	else if (c <= 0x10FFFF)
		len = 4;
	else
		len = -1;
	return (len);
}
