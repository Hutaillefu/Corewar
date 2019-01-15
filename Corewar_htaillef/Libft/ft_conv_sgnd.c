/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_conv_sgnd.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/20 12:16:27 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/05 10:46:15 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/ft_printf.h"

int		ft_conv_d(va_list args, t_prnt *p, const char *format)
{
	if (format[p->i] == 'D')
		p->l = 1;
	p->spe = format[p->i];
	p->arg = ft_check_sgnd(p, args);
	return (ft_display_numb(p));
}
