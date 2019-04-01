/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   extractor.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: htaillef <htaillef@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/07 14:55:36 by htaillef     #+#   ##    ##    #+#       */
/*   Updated: 2018/02/20 17:22:19 by htaillef    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

/*
 ** Setup flag(s) of the format.
 ** Resize the string pointed by str if flag(s) found.
*/

void	check_flags(char **str, t_format **format)
{
	enum e_bool flag_found;

	flag_found = TRUE;
	if (!str)
		return ;
	if (**str == '-')
		(*format)->flags->left_justify = TRUE;
	else if (**str == '0')
		(*format)->flags->padding = TRUE;
	else if (**str == '+')
		(*format)->flags->positive = TRUE;
	else if (**str == ' ')
		(*format)->flags->blank = TRUE;
	else if (**str == '#')
		(*format)->flags->diese = TRUE;
	else
		flag_found = FALSE;
	if (flag_found)
	{
		(*str)++;
		check_flags(str, format);
	}
}

/*
 ** Setup the int pointed by val with the number at the begin of str.
 ** Resize the string pointed by str if a number was found.
*/

void	check_width(char **str, size_t *val)
{
	int		i;
	char	*res;
	int		y;

	if (!str)
		return ;
	i = 0;
	while ((*str)[i] && ft_isdigit(((*str)[i])))
		i++;
	if (i == 0)
		return ;
	res = (char *)malloc(sizeof(char) * (i + 1));
	if (!res)
		return ;
	y = 0;
	while (y < i)
	{
		res[y] = (*str)[y];
		y++;
	}
	res[y] = '\0';
	*val = ft_atoi(res);
	ft_memdel((void**)&res);
	*str += i;
}

/*
 ** Setup the format's modifier.
 ** Resize the string pointed by str if a modifier was found.
*/

void	check_modifier(char **str, t_format **format)
{
	if (!(*str))
		return ;
	if (ft_strlen(*str) >= 2 && (*str)[0] == 'h' && (*str)[1] == 'h')
		(*format)->modifier = ft_strdup("hh");
	else if (ft_strlen(*str) >= 2 && (*str)[0] == 'l' && (*str)[1] == 'l')
		(*format)->modifier = ft_strdup("ll");
	else if (*str[0] == 'h')
		(*format)->modifier = ft_strdup("h");
	else if (*str[0] == 'l')
		(*format)->modifier = ft_strdup("l");
	else if (*str[0] == 'j')
		(*format)->modifier = ft_strdup("j");
	else if (*str[0] == 'z')
		(*format)->modifier = ft_strdup("z");
	if (((*format)->modifier))
		*str += ft_strlen((*format)->modifier);
}

/*
 ** Setup the format's period.
 ** Resize the string pointed by str if a period was found.
*/

void	check_period(char **str, t_format **format)
{
	if (!(*str))
		return ;
	if (**str == '.')
	{
		(*format)->period = TRUE;
		(*str)++;
	}
}

/*
 ** Setup the format's type.
 ** Resize the string pointed by str if a type was found.
*/

void	check_type(char **str, t_format **format)
{
	if (!(*str))
		return ;
	if (**str == 'd' || **str == 'D' || **str == 'i' || **str == 'o' ||
		**str == 'O' || **str == 'u' || **str == 'U' || **str == 'x' ||
		**str == 'X' || **str == 'p')
	{
		(*format)->type = **str;
		(*format)->is_numeric = TRUE;
		(*str)++;
	}
	else if (**str == 's' || **str == 'S' ||
		**str == 'c' || **str == 'C' || **str == '%')
	{
		(*format)->type = **str;
		(*str)++;
	}
}
