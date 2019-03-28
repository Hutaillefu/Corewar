/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_parse.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: quruiz <quruiz@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/27 16:03:04 by quruiz       #+#   ##    ##    #+#       */
/*   Updated: 2019/03/28 14:06:44 by quruiz      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_find_type(char *begin)
{
	int		i;
	char	*map;

	i = 1;
	map = "0123456789-+#*. lhjzt";
	while (begin[i] != '\0')
	{
		if (ft_strchr(map, (int)begin[i]) != NULL)
			i++;
		else
			break ;
	}
	if (i == 1 && begin[i - 1] == '%' && begin[i] == '\0')
		return (begin);
	return (begin + i);
}

void	ft_clean_struct(t_sgmt *box)
{
	box->flag->prec = 0;
	box->flag->wid = 0;
	box->flag->sharp = 0;
	box->flag->zero = 0;
	box->flag->moins = 0;
	box->flag->plus = 0;
	box->flag->space = 0;
	box->flag->h = 0;
	box->flag->l = 0;
	box->flag->j = 0;
	box->flag->z = 0;
	box->flag->dot = 0;
	box->flag->type = 0;
	box->i = 1;
	box->err = 0;
	box->set = 1;
}

int		ft_flag_detect(t_sgmt *box, va_list arg)
{
	int		ret;
	int		tmp;

	ret = 0;
	tmp = 0;
	while (box)
	{
		box->c = 0;
		box->err = 0;
		if (box->str && box->str[0] == '%')
		{
			box->flag = (t_flag *)malloc(sizeof(t_flag));
			ft_clean_struct(box);
			ft_main_parsing(box, arg);
			box->flag->type = (int)box->str[ft_strlen(box->str) - 1];
			ft_dispatch(box, arg);
			free(box->flag);
		}
		else
			box->set = 0;
		box = box->next;
	}
	return (ret);
}

void	ft_format_cutter(t_sgmt *box, char *tmp, int fd)
{
	char	*begin;
	char	*end;
	char	*substr;

	begin = tmp;
	end = tmp;
	while (*begin != '\0')
	{
		substr = NULL;
		box->fd = fd;
		if (*begin == '%')
			end = ft_find_type(begin) + 1;
		else if ((substr = ft_strchr(begin, '%')) == NULL)
			end = begin + ft_strlen(begin);
		else
			end = substr;
		box->str = ft_strsub(begin, 0, end - begin);
		begin = end++;
		if (*begin != '\0')
		{
			box->next = malloc(sizeof(t_sgmt));
			box = box->next;
			box->next = NULL;
		}
	}
}
