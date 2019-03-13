/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   display.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: htaillef <htaillef@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/06 19:35:21 by htaillef     #+#   ##    ##    #+#       */
/*   Updated: 2018/02/20 17:19:35 by htaillef    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

char		*process_type_with_modifier(t_format *infos, va_list *args)
{
	if (infos->type == '%')
		return (ft_strdup("%"));
	if (infos->type == 'i' || infos->type == 'd' || infos->type == 'D')
		return (process_int(infos, va_arg(*args, void *)));
	if (infos->type == 'u' || infos->type == 'U')
		return (process_uint)(infos, va_arg(*args, void *));
	if (infos->type == 'S' || (infos->type == 's' && infos->modifier
		&& ft_strcmp(infos->modifier, "l") == 0))
		return (process_wstr(va_arg(*args, void *)));
	if (infos->type == 's')
		return (process_string(va_arg(*args, void *)));
	if (infos->type == 'X' || infos->type == 'x')
		return (process_hexa(infos, va_arg(*args, void *)));
	if (infos->type == 'o' || infos->type == 'O')
		return (process_octal(infos, va_arg(*args, void *)));
	if (infos->type == 'C' || (infos->type == 'c' &&
		infos->modifier && ft_strcmp(infos->modifier, "l") == 0))
		return (process_wchar(va_arg(*args, void *)));
	if (infos->type == 'c')
		return (process_char(va_arg(*args, void *)));
	if (infos->type == 'p')
		return (ft_itoall_base((long)va_arg(*args, void *), 16, FALSE));
	return (ft_strdup(""));
}

/*
 ** Put in add buffer string according to format flags.
*/

void		process_add_buffer(char **add, t_format *format, char *res)
{
	if (format->flags->blank && !(format->flags->positive) &&
		format->is_numeric && !(format->is_negative) &&
		(format->type == 'D' || format->type == 'd' || format->type == 'i'))
		*add = ft_strdup(" ");
	if (format->flags->positive && format->is_numeric && (format->type == 'D' ||
		format->type == 'd' || format->type == 'i') && !(format->is_negative))
		*add = ft_strdup("+");
	if (format->is_numeric && format->is_negative)
		*add = ft_strdup("-");
	if (format->flags->diese && format->is_numeric)
	{
		if (ft_strcmp(res, "0") != 0 && ft_strlen(res) > 0)
		{
			if (format->type == 'x')
				*add = ft_strdup("0x");
			if (format->type == 'X')
				*add = ft_strdup("0X");
			if (format->type == 'o' || format->type == 'O')
				*add = ft_strdup("0");
		}
	}
	if (format->type == 'p')
		*add = ft_strdup("0x");
}

/*
 ** Makes res buffer bigger or smaller according to format precision.
*/

void		process_precision(char **res, t_format *format)
{
	char *res1;
	char *ret;

	if (format->is_numeric && format->precision > 0)
	{
		while (ft_strlen(*res) < format->precision)
		{
			ret = *res;
			*res = ft_strjoin("0", *res);
			ft_memdel((void **)&ret);
		}
	}
	else if (format->precision > 0 && (format->type == 's'
		|| format->type == 'S'))
	{
		res1 = (char *)ft_memalloc(format->precision + 1);
		ft_strncpy(res1, *res, format->precision);
		*res = res1;
	}
}

enum e_bool	process_final1(int addlen, char *res, t_format *format,
	char **final)
{
	if ((format->type == 'c' ? 1 : ft_strlen(res)) + addlen < format->min_width)
	{
		if (format->type == 'c' && ft_strcmp(res, "^@") == 0)
		{
			if (format->flags->padding && !format->flags->left_justify)
				*final = ft_init(format->min_width + 1, '0');
			else
				*final = ft_init(format->min_width + 1, ' ');
		}
		else if (format->flags->padding && !format->flags->left_justify &&
			!(format->is_numeric && format->period))
			*final = ft_init(format->min_width, '0');
		else
		{
			if (!format->type)
				*final = ft_init(ft_strlen(res) > 0 ? format->min_width
					: format->min_width - 1, ' ');
			else
				*final = ft_init(format->min_width, ' ');
		}
		return (FALSE);
	}
	return (TRUE);
}

/*
 ** Inits final buffer with correct size and char according
 ** to format flags padding and width
*/

enum e_bool	process_final(char **final, char *res,
	t_format *format, char *add)
{
	int		addlen;

	addlen = add != NULL ? ft_strlen(add) : 0;
	if (!process_final1(addlen, res, format, final))
		return (FALSE);
	else
	{
		if (add)
			*final = ft_strjoin(add, res);
		else
			*final = ft_strdup(res);
		return (TRUE);
	}
}
