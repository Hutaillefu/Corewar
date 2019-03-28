/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: quruiz <quruiz@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/11 19:07:40 by quruiz       #+#   ##    ##    #+#       */
/*   Updated: 2019/03/28 14:07:16 by quruiz      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdarg.h>
#include "ft_printf.h"

void	ft_freeing(t_sgmt *head, char *format)
{
	t_sgmt *tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		if (tmp->str != NULL)
			free(tmp->str);
		free(tmp);
	}
	free(format);
}

int		ft_printing(t_sgmt *box)
{
	int			ret;
	t_sgmt		*tmp;

	ret = 0;
	tmp = box;
	while (tmp)
	{
		if (tmp->str != NULL)
		{
			if (tmp->c != 0)
				ret++;
			if (tmp->c == -1)
				ft_putchar_fd('\0', box->fd);
			ret += ft_strlen(tmp->str);
			ft_putstr_fd(tmp->str, tmp->fd);
			if (tmp->c == 1)
				ft_putchar_fd('\0', box->fd);
		}
		if (tmp->set == -1)
			break ;
		tmp = tmp->next;
	}
	return (!tmp ? ret : -1);
}

int		ft_verif(t_sgmt *box)
{
	t_sgmt	*tmp;
	t_sgmt	*cur;

	cur = box;
	tmp = box;
	while (cur)
	{
		if (cur->set && tmp->set != -1 && cur->err != -1)
			tmp = cur;
		if (cur->err == -1 && cur->str == NULL)
		{
			tmp->set = -1;
			return (0);
		}
		else
			cur = cur->next;
	}
	return (0);
}

int		ft_dprintf(int fd, char *format, ...)
{
	int			ret;
	char		*tmp;
	va_list		arg;
	t_sgmt		*box;

	if (format[0])
	{
		ret = 0;
		box = malloc(sizeof(t_sgmt));
		box->next = NULL;
		box->fd = fd;
		va_start(arg, format);
		tmp = ft_strdup(format);
		ft_format_cutter(box, tmp, fd);
		ft_flag_detect(box, arg);
		ft_verif(box);
		ret = ft_printing(box);
		ft_freeing(box, tmp);
		va_end(arg);
	}
	else
		return (0);
	return (ret);
}

int		ft_printf(char *format, ...)
{
	int			ret;
	char		*tmp;
	va_list		arg;
	t_sgmt		*box;

	if (format[0])
	{
		ret = 0;
		box = malloc(sizeof(t_sgmt));
		box->next = NULL;
		box->fd = 1;
		va_start(arg, format);
		tmp = ft_strdup(format);
		ft_format_cutter(box, tmp, 1);
		ft_flag_detect(box, arg);
		ft_verif(box);
		ret = ft_printing(box);
		ft_freeing(box, tmp);
		va_end(arg);
	}
	else
		return (0);
	return (ret);
}
