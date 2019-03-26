/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putwchar_fd.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: quruiz <quruiz@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/08 14:11:29 by quruiz       #+#   ##    ##    #+#       */
/*   Updated: 2018/02/09 17:49:46 by quruiz      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	ft_putwchar_fd(wchar_t c, int fd)
{
	if (c <= 0x7F)
		ft_putchar_fd(c, fd);
	else if (c <= 0x7FF)
	{
		ft_putchar_fd((c >> 6) | 0xC0, fd);
		ft_putchar_fd((c & 0x3F) | 0x80, fd);
	}
	else if (c <= 0xFFFF)
	{
		ft_putchar_fd((c >> 12) | 0xE0, fd);
		ft_putchar_fd(((c >> 6) & 0x3F) | 0x80, fd);
		ft_putchar_fd((c & 0x3F) | 0x80, fd);
	}
	else if (c <= 0x10FFFF)
	{
		ft_putchar_fd((c >> 18) | 0xF0, fd);
		ft_putchar_fd(((c >> 12) & 0x3F) | 0x80, fd);
		ft_putchar_fd(((c >> 6) & 0x3F) | 0x80, fd);
		ft_putchar_fd((c & 0x3F) | 0x80, fd);
	}
}
