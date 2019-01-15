/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putchar_print.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/23 14:18:00 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/05 10:45:27 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/ft_printf.h"

void	ft_putchar_p(char c, t_prnt *p)
{
	if (p->spe == 'C' || p->spe == 'S')
		ft_putchar_wp((wchar_t)c, p);
	write(1, &c, 1);
	p->ret++;
}

void	ft_putchar_wp(wchar_t c, t_prnt *p)
{
	if (c <= 0x7F)
		ft_putchar_p(c, p);
	else if (c <= 0x7FF)
	{
		ft_putchar_p(c >> 6 | 0xC0, p);
		ft_putchar_p((c & 0x3F) | 0x80, p);
	}
	else if (c <= 0xFFFF)
	{
		ft_putchar_p((c >> 12) | 0xe0, p);
		ft_putchar_p(((c >> 6) & 0x3f) | 0x80, p);
		ft_putchar_p((c & 0x3f) | 0x80, p);
	}
	else if (c < 0x10FFFF)
	{
		ft_putchar_p((c >> 18) | 0xf0, p);
		ft_putchar_p(((c >> 12) & 0x3f) | 0x80, p);
		ft_putchar_p(((c >> 6) & 0x3f) | 0x80, p);
		ft_putchar_p((c & 0x3f) | 0x80, p);
	}
}
