/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_display.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/27 15:21:07 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/05 10:45:45 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/ft_printf.h"

void	ft_display_arg(t_prnt *p)
{
	int i;

	i = -1;
	if (p->spe == 'c' && p->arg[0] == '\0')
		ft_putchar_p(p->arg[0], p);
	while (p->arg[++i])
		ft_putchar_p(p->arg[i], p);
	if (p->arg != NULL && (p->spe == 'c' ||
	p->spe == 'S' || p->spe == 'C' || p->spe == '%' || (p->spe == 's'
	&& p->f == 1)))
		free(p->arg);
	p->f = 0;
}

void	ft_print_space(t_prnt *p)
{
	if (p->pls == 1 || p->space == 1)
	{
		if (p->spe == 'd' || p->spe == 'D' || p->spe == 'i')
		{
			if (p->space == 1 && p->pls == 0 && p->sgn_nb == 0)
				ft_putchar_p(' ', p);
			if (p->pls == 1 && p->sgn_nb == 0)
				ft_putchar_p('+', p);
		}
	}
	if (p->sgn_nb == 1)
		ft_putchar_p('-', p);
	ft_print_hst(p);
}

void	ft_print_hst(t_prnt *p)
{
	if ((p->hst == 1 && p->arg[0] != '0') || p->spe == 'p')
	{
		if (p->spe == 'o' || p->spe == 'O' || p->spe == 'x' ||
		p->spe == 'X' || p->spe == 'p')
		{
			if ((p->spe == 'x' && p->arg != '\0') || p->spe == 'p')
			{
				ft_putchar_p('0', p);
				ft_putchar_p('x', p);
			}
			else if (p->spe == 'X' && p->arg != '\0')
			{
				ft_putchar_p('0', p);
				ft_putchar_p('X', p);
			}
			else if ((p->spe == 'o' || p->spe == 'O') && ((p->prcs <=
			(int)ft_strlen(p->arg)) || (p->got_prcs == 1 && p->prcs == 0)))
				ft_putchar_p('0', p);
		}
	}
}

void	ft_print_zro(t_prnt *p)
{
	int len;
	int i;
	int wdth;

	wdth = 0;
	len = 0;
	len = (int)ft_strlen(p->arg);
	i = -1;
	if (p->prcs == 0 && p->got_prcs == 1 && p->arg[0] == '0')
		wdth = p->wdth;
	else
		wdth = p->wdth - len;
	ft_print_zro_ftr(p, wdth);
	while (p->prcs > len++)
		ft_putchar_p('0', p);
	while (p->arg[++i])
	{
		if (p->prcs == 0 && p->got_prcs == 1 && p->arg[0] == '0')
			break ;
		else
			ft_putchar_p(p->arg[i], p);
	}
}

void	ft_print_zro_ftr(t_prnt *p, int wdth)
{
	if (p->zro == 1)
	{
		ft_print_space(p);
		ft_print_prcs(p, wdth);
	}
	else
	{
		ft_print_prcs(p, wdth);
		ft_print_space(p);
	}
}
