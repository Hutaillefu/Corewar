/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_display_num.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/03 14:54:41 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/05 10:45:50 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/ft_printf.h"

int		ft_display_numb(t_prnt *p)
{
	int i;

	i = -1;
	if (p->got_prcs == 1 && p->prcs == 0 && p->arg[0] == 0 && (p->hst == 1 &&
	(p->spe == 'o' || p->spe == 'O' || p->spe == 'p')))
	{
		p->arg = NULL;
		free(p->arg);
		p->arg[0] = '\0';
	}
	if (p->wdth > 0)
		ft_print_wdth(p);
	else if (p->wdth == 0 && p->prcs > 0)
		ft_print_prcsww(p);
	if (p->prcs == 0 && p->wdth == 0)
		ft_print_space(p);
	if (p->prcs == 0 && p->got_prcs == 1 && p->arg[0] == '0' && ((p->hst == 0)
	|| ((p->spe == 'x' || p->spe == 'X') && p->hst == 1)))
		return (1);
	while (p->arg[++i] && p->wdth == 0)
		ft_putchar_p(p->arg[i], p);
	if (p->arg)
		free(p->arg);
	return (1);
}

void	ft_print_wdth(t_prnt *p)
{
	int len;
	int i;

	i = -1;
	len = 0;
	len = (int)ft_strlen(p->arg);
	if (len < p->wdth)
	{
		if (p->neg == 1)
			ft_print_neg(p);
		else
			ft_print_zro(p);
	}
	else
	{
		ft_print_space(p);
		while (p->prcs > len++)
			ft_putchar_p('0', p);
		while (p->arg[++i])
			ft_putchar_p(p->arg[i], p);
	}
}

void	ft_print_neg(t_prnt *p)
{
	int i;
	int len;
	int wdth;

	i = -1;
	len = 0;
	wdth = 0;
	len = (int)ft_strlen(p->arg);
	wdth = p->wdth - len;
	p->zro = 0;
	ft_print_space(p);
	while (p->prcs > len++)
		ft_putchar_p('0', p);
	while (p->arg[++i])
		ft_putchar_p(p->arg[i], p);
	ft_print_prcs(p, wdth);
}

void	ft_print_prcs(t_prnt *p, int wdth)
{
	int len;

	len = 0;
	len = (int)ft_strlen(p->arg);
	if (p->pls == 1 || p->space == 1 || p->sgn_nb == 1 || (p->hst == 1 &&
	p->prcs <= len && p->arg[0] != '0' && (p->spe == 'o' || p->spe == 'O')))
		wdth--;
	if (((p->hst == 1 && (p->spe == 'x' || p->spe == 'X')) && p->arg[0] != '0')
	|| p->spe == 'p')
		wdth -= 2;
	while (p->prcs > len++)
		wdth--;
	if (p->prcs < p->wdth + (int)ft_strlen(p->arg))
	{
		while (wdth-- > 0)
		{
			if (p->zro == 1 && p->prcs == 0 && p->got_prcs == 0)
				ft_putchar_p('0', p);
			else
				ft_putchar_p(' ', p);
		}
	}
}

void	ft_print_prcsww(t_prnt *p)
{
	int len;
	int prcs;

	len = 0;
	prcs = 0;
	prcs = p->prcs;
	len = (int)ft_strlen(p->arg);
	ft_print_space(p);
	while (prcs > len-- && len > 0)
		prcs--;
	if (p->prcs > p->wdth + (int)ft_strlen(p->arg))
	{
		while (++len < prcs)
			ft_putchar_p('0', p);
	}
}
