/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_itoaull_base.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: htaillef <htaillef@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/30 13:59:57 by htaillef     #+#   ##    ##    #+#       */
/*   Updated: 2018/02/20 17:23:28 by htaillef    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_nb_digit(unsigned long long n)
{
	int i;

	i = 1;
	while (n > 9)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

static char	ft_upper_char(int n)
{
	if (n == 10)
		return ('A');
	else if (n == 11)
		return ('B');
	else if (n == 12)
		return ('C');
	else if (n == 13)
		return ('D');
	else if (n == 14)
		return ('E');
	else if (n == 15)
		return ('F');
	else
		return (n + '0');
}

static char	ft_lower_char(int n)
{
	if (n == 10)
		return ('a');
	else if (n == 11)
		return ('b');
	else if (n == 12)
		return ('c');
	else if (n == 13)
		return ('d');
	else if (n == 14)
		return ('e');
	else if (n == 15)
		return ('f');
	else
		return (n + '0');
}

static void	ft_itoa_rec(char *res, unsigned long long n, int *i,
	long long base)
{
	unsigned long long	nbase;
	enum e_bool			capital;

	if (base > 0)
		capital = TRUE;
	else
	{
		capital = FALSE;
		base = -base;
	}
	nbase = base;
	if (n < nbase)
	{
		if (capital == TRUE)
			res[*i] = ft_upper_char(n);
		else
			res[*i] = ft_lower_char(n);
		(*i)++;
	}
	else
	{
		ft_itoa_rec(res, n / nbase, i, capital ? base : -base);
		ft_itoa_rec(res, n % nbase, i, capital ? base : -base);
	}
}

char		*ft_itoaull_base(unsigned long long n, long long base,
	enum e_bool capital)
{
	char	*res;
	int		i;

	if (base > 16)
		return (NULL);
	i = 0;
	if ((res = (char *)ft_memalloc(sizeof(char) * ft_nb_digit(n) + 1)) == NULL)
		return (NULL);
	ft_itoa_rec(res, n, &i, capital ? base : -base);
	res[i] = '\0';
	return (res);
}
