/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/22 12:10:19 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/05 10:44:53 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/ft_printf.h"

char	*ft_error(char *str)
{
	if (str == NULL)
		return (NULL);
	else
		return (str);
}

void	reinit_prnt(t_prnt *p)
{
	p->hst = 0;
	p->sgn_nb = 0;
	p->pls = 0;
	p->zro = 0;
	p->neg = 0;
	p->wdth = 0;
	p->prcs = 0;
	p->space = 0;
	p->got_prcs = 0;
	p->l = 0;
	p->ll = 0;
	p->h = 0;
	p->hh = 0;
	p->j = 0;
	p->z = 0;
	p->spe = 0;
	p->f = 0;
}

t_prnt	*init_prnt(void)
{
	t_prnt *p;

	if (!(p = malloc(sizeof(t_prnt))))
		return (NULL);
	p->hst = 0;
	p->sgn_nb = 0;
	p->pls = 0;
	p->zro = 0;
	p->neg = 0;
	p->wdth = 0;
	p->prcs = 0;
	p->space = 0;
	p->got_prcs = 0;
	p->l = 0;
	p->ll = 0;
	p->h = 0;
	p->hh = 0;
	p->j = 0;
	p->z = 0;
	init_prnt_2(p);
	return (p);
}

void	init_prnt_2(t_prnt *p)
{
	p->arg = NULL;
	p->spe = 0;
	p->i = 0;
	p->buf = 0;
	p->ret = 0;
	p->tmp = 0;
	p->conv = 0;
	p->got_wdth = 0;
	p->wczro = 0;
	p->f = 0;
}

void	ft_save_str(char c, t_prnt *p)
{
	if ((c != '\0' || p->arg[0] == '\0') && p->wczro == 0)
		p->str[p->buf++] = c;
	if (p->wczro == 1)
		p->ret++;
}
