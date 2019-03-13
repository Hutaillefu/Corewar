/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   display1.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: htaillef <htaillef@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/06 19:35:21 by htaillef     #+#   ##    ##    #+#       */
/*   Updated: 2018/02/20 17:18:43 by htaillef    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

/*
 ** Joins add and res buffer in final buffer according
 ** to format left justify or padding
*/

void	process_justify(char **final, t_format *format, char *add, char *res)
{
	int add_insert;
	int	res_insert;

	add_insert = -1;
	res_insert = ft_strlen(*final) - ft_strlen(res);
	if (format->period && format->precision == 0 &&
		(format->type == 's' || format->type == 'S'))
		return ;
	if (format->flags->padding && !(format->flags->left_justify)
		&& !(format->is_numeric && format->period) && add)
		add_insert = 0;
	else if (format->flags->padding && !(format->flags->left_justify)
		&& format->precision > 0 && add)
		add_insert = ft_strlen(*final) - format->precision - ft_strlen(add);
	else if (format->flags->left_justify)
	{
		if (add)
			add_insert = 0;
		res_insert = add != NULL ? ft_strlen(add) : 0;
	}
	else if (add)
		add_insert = ft_strlen(*final) - ft_strlen(res) - ft_strlen(add);
	if (add && add_insert != -1)
		ft_write(final, add, add_insert);
	ft_write(final, res, res_insert);
}

char	*process_flags_and_precision(char *res, t_format *format)
{
	char *final;
	char *add;

	final = NULL;
	add = NULL;
	process_add_buffer(&add, format, res);
	if (format->period && format->precision == 0 && (ft_strcmp(res, "0") == 0
		|| (format->type == 's' || format->type == 'S')))
	{
		if (!(format->flags->diese && (format->type == 'o'
			|| format->type == 'O')))
			res = ft_strdup("");
	}
	process_precision(&res, format);
	if (process_final(&final, res, format, add))
	{
		ft_memdel((void **)&add);
		ft_memdel((void**)&res);
		return (final);
	}
	process_justify(&final, format, add, res);
	ft_memdel((void **)&add);
	ft_memdel((void **)&res);
	return (final);
}

int		display_format(t_format *infos, va_list *args, t_logs *logs)
{
	char		*res;
	char		*final;
	int			len;
	enum e_bool	isnull;

	if (!(res = process_type_with_modifier(infos, args)))
		return (-1);
	isnull = ft_strcmp(res, "^@") == 0;
	if (res[0] == '-' && infos->is_numeric)
	{
		res = ft_strsub(res, 1, ft_strlen(res) - 1);
		infos->is_negative = TRUE;
	}
	if (!(final = process_flags_and_precision(res, infos)))
		return (0);
	if (isnull)
		customput(final);
	else
		add_logs(logs, final);
		//ft_putstr(final);
	len = ft_strlen(final);
	ft_memdel((void **)&final);
	return (isnull ? len - 1 : len);
}
