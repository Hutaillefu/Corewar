/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   helper.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: htaillef <htaillef@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/06 19:35:21 by htaillef     #+#   ##    ##    #+#       */
/*   Updated: 2018/02/20 15:47:22 by htaillef    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_init(size_t len, char c)
{
	char	*res;
	size_t	i;

	res = ft_memalloc(len + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (i < len)
	{
		res[i] = c;
		i++;
	}
	res[i] = '\0';
	return (res);
}

/*
 ** Puts new in src at start_index
*/

void	ft_write(char **src, char *new, size_t start_index)
{
	size_t y;

	y = 0;
	while (y < ft_strlen(new))
	{
		(*src)[start_index + y] = new[y];
		y++;
	}
}

void	customput(char *final)
{
	int		i;
	char	c;

	i = 0;
	c = 0;
	while (final[i])
	{
		if (final[i] == '^' && final[i + 1] && final[i + 1] == '@')
		{
			write(1, &c, 1);
			i++;
		}
		else
			ft_putchar(final[i]);
		i++;
	}
}
