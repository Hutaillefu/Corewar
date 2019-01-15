/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_conv_pp.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/29 10:19:13 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/05 10:46:19 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/ft_printf.h"

int		ft_conv_p(va_list args, t_prnt *p, const char *format)
{
	uintmax_t nb;

	nb = 0;
	p->spe = format[p->i];
	nb = va_arg(args, uintmax_t);
	p->arg = ft_itoa_base_low(nb, 16);
	return (ft_display_numb(p));
}

int		ft_conv_prc(t_prnt *p, const char *format)
{
	p->spe = format[p->i];
	if (!(p->arg = malloc(sizeof(char) * 2)))
		return (0);
	p->arg[0] = '%';
	p->arg[1] = '\0';
	return (ft_display_char(p));
}
