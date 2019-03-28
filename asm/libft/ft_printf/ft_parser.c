/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_parser.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: quruiz <quruiz@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/22 15:38:59 by quruiz       #+#   ##    ##    #+#       */
/*   Updated: 2018/05/04 15:15:50 by quruiz      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_get_flags(t_sgmt *box)
{
	while (box->str[box->i])
	{
		if (box->str[box->i] == '#')
			;
		else if (box->str[box->i] == '0')
			FLAGS->zero += 1;
		else if (box->str[box->i] == '-')
			FLAGS->moins = 1;
		else if (box->str[box->i] == '+')
			;
		else if (box->str[box->i] == ' ')
			FLAGS->space += 1;
		else
			break ;
		(box->i)++;
	}
	if (ft_strchr(box->str, 43) != NULL)
		FLAGS->plus = 1;
	if (ft_strchr(box->str, 35) != NULL)
		FLAGS->sharp = 1;
}

void	ft_get_width(t_sgmt *box, va_list arg)
{
	if (box->str[box->i] == '*')
	{
		FLAGS->wid = va_arg(arg, int);
		box->i += 1;
	}
	if (box->str[box->i] >= '0' && box->str[box->i] <= '9')
	{
		FLAGS->wid = 0;
		while (box->str[box->i] >= '0' && box->str[box->i] <= '9')
		{
			FLAGS->wid = FLAGS->wid * 10;
			FLAGS->wid += (box->str[box->i] - 48);
			box->i += 1;
		}
	}
	if (box->str[box->i] == '*')
	{
		FLAGS->wid = va_arg(arg, int);
		box->i += 1;
	}
	if (FLAGS->moins == 1)
		FLAGS->wid *= -1;
}

void	ft_get_prec(t_sgmt *box, va_list arg)
{
	while (box->str[box->i] == '.')
	{
		FLAGS->dot = 1;
		box->i += 1;
	}
	if (box->str[box->i] == '-' || box->str[box->i] == '+')
		(box->i)++;
	if (box->str[box->i] == '*')
	{
		FLAGS->prec = va_arg(arg, int);
		box->i += 1;
	}
	if (box->str[box->i] >= '0' && box->str[box->i] <= '9')
	{
		while (box->str[box->i] >= '0' && box->str[box->i] <= '9')
		{
			FLAGS->prec = FLAGS->prec * 10;
			FLAGS->prec += (box->str[box->i] - 48);
			box->i += 1;
		}
	}
	if (box->str[box->i] == '.' || !FLAGS->dot)
		FLAGS->prec = 0;
}

void	ft_get_size(t_sgmt *box)
{
	while (box->str[box->i])
	{
		if (box->str[box->i] == 'l')
			FLAGS->l += 1;
		else if (box->str[box->i] == 'h')
			FLAGS->h += 1;
		else if (box->str[box->i] == 'j')
			FLAGS->j += 1;
		else if (box->str[box->i] == 'z')
			FLAGS->z += 1;
		else
			break ;
		(box->i)++;
	}
}

void	ft_main_parsing(t_sgmt *box, va_list arg)
{
	ft_get_flags(box);
	ft_get_width(box, arg);
	ft_get_prec(box, arg);
	ft_get_size(box);
}
