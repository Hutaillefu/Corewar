/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_display_char.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/03 14:54:45 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/05 10:45:56 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/ft_printf.h"

int		ft_display_char(t_prnt *p)
{
	if (p->got_prcs == 1 && (p->spe != 'c' && p->spe != 'C' && p->spe != '%'))
		ft_print_prcs_char(p);
	if (p->wdth > 0)
		ft_print_wdth_char(p);
	else if (p->wdth == 0)
		ft_display_arg(p);
	return (1);
}

void	ft_print_prcs_char(t_prnt *p)
{
	if (p->got_prcs == 1 && (p->spe != 'c' && p->spe != 'C'))
	{
		if (p->prcs == 0 && p->got_prcs == 1 && p->spe != '%')
			p->arg = "\0";
		else if (p->spe == 's')
		{
			p->f = 1;
			p->arg = ft_strsub(p->arg, 0, p->prcs);
		}
	}
}

void	ft_print_wdth_char(t_prnt *p)
{
	int len;

	len = (int)ft_strlen(p->arg);
	if (len < p->wdth)
	{
		if (p->neg == 1)
			ft_print_neg_char(p);
		else
			ft_print_zro_char(p);
	}
	else
		ft_display_arg(p);
}

void	ft_print_neg_char(t_prnt *p)
{
	int len;
	int wdth;

	len = (int)ft_strlen(p->arg);
	if (p->arg[0] == '\0' && p->spe == 'c')
		len = 1;
	wdth = p->wdth - len;
	p->zro = 0;
	ft_display_arg(p);
	while (wdth-- > 0)
		ft_putchar_p(' ', p);
}

void	ft_print_zro_char(t_prnt *p)
{
	int len;
	int wdth;

	len = (int)ft_strlen(p->arg);
	if (p->arg[0] == '\0' && p->spe == 'c')
		len = 1;
	wdth = p->wdth - len;
	while (wdth-- > 0)
	{
		if (p->zro == 1)
			ft_putchar_p('0', p);
		else
			ft_putchar_p(' ', p);
	}
	ft_display_arg(p);
}
