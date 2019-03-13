/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   numeric_process.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: htaillef <htaillef@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/06 19:35:21 by htaillef     #+#   ##    ##    #+#       */
/*   Updated: 2018/02/20 17:23:48 by htaillef    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

char	*process_int(t_format *infos, void *value)
{
	if (infos->modifier)
	{
		if (ft_strcmp(infos->modifier, "l") == 0)
			return (ft_itoall((long)value));
		else if (ft_strcmp(infos->modifier, "ll") == 0)
			return (ft_itoall((long long)value));
		else if (ft_strcmp(infos->modifier, "z") == 0)
			return (ft_itoall((ssize_t)value));
		else if (ft_strcmp(infos->modifier, "j") == 0)
			return (ft_itoall((intmax_t)value));
		else if (ft_strcmp(infos->modifier, "hh") == 0 && infos->type == 'D')
			return (ft_itoall((long)value));
		else if (ft_strcmp(infos->modifier, "hh") == 0)
			return (ft_itoall(((char)value)));
		else if (ft_strcmp(infos->modifier, "h") == 0 && infos->type == 'D')
			return (ft_itoall((long)value));
		else if (ft_strcmp(infos->modifier, "h") == 0)
			return (ft_itoall(((short)value)));
	}
	if (infos->type == 'D')
		return (ft_itoall((long)value));
	else
		return (ft_itoall((int)value));
}

char	*process_uint(t_format *infos, void *value)
{
	if (infos->modifier)
	{
		if (ft_strcmp(infos->modifier, "l") == 0)
			return (ft_itoaull((unsigned long)value));
		if (ft_strcmp(infos->modifier, "ll") == 0)
			return (ft_itoaull((unsigned long long)value));
		if (ft_strcmp(infos->modifier, "j") == 0)
			return (ft_itoaull((uintmax_t)value));
		if (ft_strcmp(infos->modifier, "z") == 0)
			return (ft_itoaull((size_t)value));
		if (ft_strcmp(infos->modifier, "h") == 0 && infos->type == 'U')
			return (ft_itoaull((unsigned long)value));
		if (ft_strcmp(infos->modifier, "h") == 0)
			return (ft_itoaull((unsigned short)value));
		if (ft_strcmp(infos->modifier, "hh") == 0 && infos->type == 'U')
			return (ft_itoaull((unsigned long)value));
		if (ft_strcmp(infos->modifier, "hh") == 0)
			return (ft_itoaull((unsigned char)value));
	}
	if (infos->type == 'U')
		return (ft_itoaull((unsigned long)value));
	return (ft_itoaull((unsigned int)value));
}

char	*process_hexa(t_format *infos, void *value)
{
	enum e_bool maj;

	maj = infos->type == 'X';
	if (infos->modifier)
	{
		if (ft_strcmp(infos->modifier, "l") == 0)
			return (ft_itoaull_base((unsigned long)value, 16, maj));
		if (ft_strcmp(infos->modifier, "ll") == 0)
			return (ft_itoaull_base((unsigned long long)value, 16, maj));
		if (ft_strcmp(infos->modifier, "z") == 0)
			return (ft_itoaull_base((size_t)value, 16, maj));
		if (ft_strcmp(infos->modifier, "h") == 0)
			return (ft_itoall_base((unsigned short)value, 16, maj));
		if (ft_strcmp(infos->modifier, "h") == 0)
			return (ft_itoaull_base((unsigned long)value, 16, maj));
		if (ft_strcmp(infos->modifier, "hh") == 0)
			return (ft_itoaull_base((unsigned char)value, 16, maj));
		if (ft_strcmp(infos->modifier, "j") == 0)
			return (ft_itoaull_base((uintmax_t)value, 16, maj));
	}
	return (ft_itoaull_base((unsigned int)value, 16, maj));
}

char	*process_octal(t_format *infos, void *value)
{
	if (infos->modifier)
	{
		if (ft_strcmp(infos->modifier, "l") == 0)
			return (ft_itoaull_base((unsigned long)value, 8, FALSE));
		if (ft_strcmp(infos->modifier, "ll") == 0)
			return (ft_itoaull_base((unsigned long long)value, 8, FALSE));
		if (ft_strcmp(infos->modifier, "z") == 0)
			return (ft_itoaull_base((size_t)value, 8, FALSE));
		if (ft_strcmp(infos->modifier, "h") == 0)
			return (ft_itoall_base((unsigned short)value, 8, FALSE));
		if (ft_strcmp(infos->modifier, "h") == 0)
			return (ft_itoaull_base((unsigned long)value, 8, FALSE));
		if (ft_strcmp(infos->modifier, "j") == 0)
			return (ft_itoaull_base((uintmax_t)value, 8, FALSE));
		if (ft_strcmp(infos->modifier, "hh") == 0 && infos->type == 'O')
			return (ft_itoaull_base((unsigned long)value, 8, FALSE));
		if (ft_strcmp(infos->modifier, "hh") == 0)
			return (ft_itoaull_base((unsigned char)value, 8, FALSE));
	}
	if (infos->type == 'O')
		return (ft_itoaull_base((unsigned long)value, 8, FALSE));
	return (ft_itoall_base((unsigned int)value, 8, FALSE));
}
