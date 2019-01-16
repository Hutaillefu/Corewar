/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_conv_wchar.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/31 15:02:33 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/05 10:46:07 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/ft_printf.h"

int		ft_conv_bc(va_list args, t_prnt *p)
{
	wchar_t	wc;

	wc = va_arg(args, wchar_t);
	if (ft_check_wchar(wc) == -1)
	{
		p->buf -= p->tmp;
		ft_putstr_p(p->str, p);
		return (-1);
	}
	p->arg = ft_putchar_to_char(wc);
	if (p->arg[0] == 0)
		p->wczro = 1;
	if (wc == '\0')
		p->ret++;
	return (ft_display_char(p));
}

int		ft_conv_bs(va_list args, t_prnt *p)
{
	wchar_t	*ws;

	ws = va_arg(args, wchar_t *);
	if (ws == NULL)
		ws = L"(null)";
	p->arg = ft_modif_wchar_to_char(ws, p);
	if (p->arg == NULL)
		return (-1);
	return (ft_display_char(p));
}

char	*ft_modif_wchar_to_char(wchar_t *ws, t_prnt *p)
{
	int		len;
	int		i;
	int		cn;

	i = 0;
	cn = 0;
	len = 0;
	len = ft_wstrlen(ws);
	if (len > p->prcs && p->got_prcs == 1)
	{
		while ((cn + ft_wclen(ws[i])) <= p->prcs)
		{
			cn += ft_wclen(ws[i]);
			i++;
		}
		len = cn;
	}
	return (ft_modif_wchar_next(ws, len, p));
}

char	*ft_modif_wchar_next(wchar_t *ws, int len, t_prnt *p)
{
	char	*str;
	int		k;
	int		i;

	i = 0;
	k = 0;
	if (!(str = malloc(sizeof(char) * len + 1)))
		return (NULL);
	if (len == 0)
		p->f = 1;
	str[len] = '\0';
	while (i < len)
	{
		i = ft_putwchar_to_char(ws[k], str, i);
		if (i == -1)
		{
			free(str);
			return (NULL);
		}
		k++;
	}
	return (str);
}
