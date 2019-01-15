/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_conv_usgnd.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/20 12:38:01 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/05 10:46:11 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/ft_printf.h"

int		ft_conv_u(va_list args, t_prnt *p, const char *format)
{
	if (format[p->i] == 'U')
		p->l = 1;
	p->spe = format[p->i];
	p->arg = ft_check_usgnd(p, args);
	return (ft_display_numb(p));
}

int		ft_conv_o(va_list args, t_prnt *p, const char *format)
{
	if (format[p->i] == 'O')
		p->l = 1;
	p->spe = format[p->i];
	p->arg = ft_check_usgnd(p, args);
	return (ft_display_numb(p));
}

int		ft_conv_x(va_list args, t_prnt *p, const char *format)
{
	p->spe = format[p->i];
	p->arg = ft_check_usgnd(p, args);
	return (ft_display_numb(p));
}
