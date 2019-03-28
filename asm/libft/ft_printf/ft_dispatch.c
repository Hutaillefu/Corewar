/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_dispatch.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: quruiz <quruiz@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/08 13:42:19 by quruiz       #+#   ##    ##    #+#       */
/*   Updated: 2018/03/28 15:39:37 by quruiz      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_undefined_type(t_sgmt *box, char c)
{
	char	*str;
	char	*ch;

	if (ft_strchr("0123456789-+#*. lhjzt", c) != NULL)
		str = ft_strdup("\0");
	else
	{
		ch = ft_strnew(1);
		ch[0] = c;
		if (FLAGS->wid != 0)
			str = ft_printf_c_wid(box, ch);
		else
			str = ch;
	}
	return (str);
}

char	*ft_choose_type(t_sgmt *box, va_list arg, char c)
{
	char	*str;

	if (c == '%')
		str = ft_printf_percent(box);
	else if (c == 'c')
		str = ft_printf_c(box, arg);
	else if (c == 'd' || c == 'i')
		str = ft_printf_d(box, arg);
	else if (c == 's')
		str = ft_printf_s(box, arg);
	else if (c == 'x' || c == 'X')
		str = ft_printf_x(box, 16, arg);
	else if (c == 'o')
		str = ft_printf_o(box, 8, arg);
	else if (c == 'u')
		str = ft_printf_o(box, 10, arg);
	else if (c == 'p')
		str = ft_printf_p(box, 16, arg);
	else
		str = ft_undefined_type(box, c);
	return (str);
}

void	ft_dispatch(t_sgmt *box, va_list arg)
{
	char	c;
	int		ret;
	int		i;

	c = (char)FLAGS->type;
	ret = 0;
	i = 1;
	if (c == 'S' || c == 'D' || c == 'O' || c == 'U' || c == 'C')
	{
		FLAGS->l = 1;
		FLAGS->type += 32;
		c = FLAGS->type;
	}
	if (ft_strlen(box->str) == 1 && c == '%')
		c = '\0';
	free(box->str);
	box->str = ft_choose_type(box, arg, c);
}
