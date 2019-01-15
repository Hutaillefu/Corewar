/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_conv_char.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/20 12:16:24 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/05 10:46:23 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/ft_printf.h"

int		ft_conv_c(va_list args, t_prnt *p, const char *format)
{
	char c;

	p->spe = format[p->i];
	c = va_arg(args, int);
	if (!(p->arg = malloc(sizeof(char) * 2)))
		return (0);
	p->arg[0] = c;
	p->arg[1] = '\0';
	return (ft_display_char(p));
}

int		ft_conv_s(va_list args, t_prnt *p, const char *format)
{
	p->spe = format[p->i];
	p->arg = va_arg(args, char *);
	if (p->arg == NULL)
		p->arg = "(null)";
	return (ft_display_char(p));
}
