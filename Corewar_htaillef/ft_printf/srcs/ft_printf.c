/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: htaillef <htaillef@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/05 15:58:09 by htaillef     #+#   ##    ##    #+#       */
/*   Updated: 2018/02/20 15:45:34 by htaillef    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

void	end(char *buf, t_logs *logs)
{
	add_logs(logs, buf);
	//ft_putstr(buf);
	ft_memdel((void **)&buf);
}

void	nln(char **buf, char **format, int *chars)
{
	*buf = ft_strnjoin(*buf, (*format)++, 1);
	(*chars)++;
}

void	nln1(char **buf, char **format, t_format **infos, t_logs *logs)
{
	add_logs(logs, *buf);
	//ft_putstr(*buf);
	ft_memdel((void **)buf);
	*buf = ft_strdup("");
	(*format)++;
	*infos = extract(format);
}

int		process(char **format, va_list *args, t_logs *logs)
{
	int			i;
	int			chars;
	t_format	*infos;
	char		*buf;
	int			res;

	buf = ft_strdup("");
	chars = 0;
	i = 0;
	while (**format)
	{
		if ((**format) == '%')
		{
			nln1(&buf, format, &infos, logs);
			res = display_format(infos, args, logs);
			if (res == -1)
				return (res);
			chars += res;
			free_format(&infos);
		}
		else
			nln(&buf, format, &chars);
	}
	end(buf, logs);
	return (chars);
}

int		ft_printf(t_logs *logs, const char *restrict format, ...)
{
	int		chars;
	va_list	args;

	if (!format)
		return (-1);
	va_start(args, format);
	init_logs(logs);
	chars = process((char **)&format, &args, logs);
	va_end(args);
	return (chars);
}
