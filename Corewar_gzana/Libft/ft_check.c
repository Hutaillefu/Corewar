/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_check.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/29 10:34:34 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/05 10:46:26 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/ft_printf.h"

char	*ft_check_sgnd(t_prnt *p, va_list args)
{
	intmax_t	nb;
	uintmax_t	nbr;

	nb = va_arg(args, intmax_t);
	if (p->z == 1)
		nb = (size_t)nb;
	else if (p->j == 1)
		nb = (intmax_t)nb;
	else if (p->l == 1)
		nb = (long)nb;
	else if (p->ll == 1)
		nb = (long long)nb;
	else if (p->hh == 1)
		nb = (signed char)nb;
	else if (p->h == 1)
		nb = (short int)nb;
	else
		nb = (int)nb;
	if (nb < 0)
	{
		p->sgn_nb = 1;
		nb = -nb;
	}
	nbr = nb;
	return (ft_itoa_base_low(nbr, 10));
}

char	*ft_check_usgnd(t_prnt *p, va_list args)
{
	uintmax_t	nb;

	nb = 0;
	nb = va_arg(args, uintmax_t);
	if (p->z == 1)
		nb = (size_t)nb;
	else if (p->j == 1)
		nb = (uintmax_t)nb;
	else if (p->l == 1)
		nb = (unsigned long)nb;
	else if (p->ll == 1)
		nb = (unsigned long long)nb;
	else if (p->hh == 1)
		nb = (unsigned char)nb;
	else if (p->h == 1)
		nb = (unsigned short int)nb;
	else
		nb = (unsigned int)nb;
	if (p->spe == 'o' || p->spe == 'O')
		return (ft_itoa_base_low(nb, 8));
	else if (p->spe == 'u' || p->spe == 'U')
		return (ft_itoa_base_low(nb, 10));
	else
		return (p->spe == 'x' ? ft_itoa_base_low(nb, 16) :
		ft_itoa_base_up(nb, 16));
}
