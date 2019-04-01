/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putnbr_fd.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: htaillef <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/30 14:05:01 by htaillef     #+#   ##    ##    #+#       */
/*   Updated: 2017/11/30 14:05:04 by htaillef    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int n1;

	n1 = n;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n1 = -n1;
	}
	if (n1 < 10)
		ft_putchar_fd(n1 + '0', fd);
	else
	{
		ft_putnbr_fd(n1 / 10, fd);
		ft_putnbr_fd(n1 % 10, fd);
	}
}
