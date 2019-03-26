/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   struct_manager.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: htaillef <htaillef@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/07 14:39:28 by htaillef     #+#   ##    ##    #+#       */
/*   Updated: 2018/02/20 15:55:10 by htaillef    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

/*
 ** Initialize a new fresh t_flags object.
 ** Return the object or NULL if error.
*/

static t_flags	*new_flags(void)
{
	t_flags *flags;

	flags = (t_flags *)malloc(sizeof(t_flags));
	if (!flags)
		return (NULL);
	flags->left_justify = FALSE;
	flags->padding = FALSE;
	flags->positive = FALSE;
	flags->blank = FALSE;
	flags->diese = FALSE;
	return (flags);
}

/*
 ** Initilize a new fresh t_format object.
 ** Return the object or NULL if error.
*/

t_format		*new_format(void)
{
	t_format	*format;
	t_flags		*flags;

	format = (t_format *)malloc(sizeof(t_format));
	if (!format)
		return (NULL);
	flags = new_flags();
	if (!flags)
		return (NULL);
	format->flags = flags;
	format->min_width = 0;
	format->period = FALSE;
	format->precision = 0;
	format->modifier = NULL;
	format->type = '\0';
	format->is_numeric = FALSE;
	format->is_negative = FALSE;
	return (format);
}

void			free_format(t_format **format)
{
	if (!format)
		return ;
	if (*format)
	{
		ft_memdel((void **)&((*format)->flags));
		ft_memdel((void **)&((*format)->modifier));
		ft_memdel((void **)format);
	}
}

/*
 ** Create a new fresh format based on str information. Resize str.
 ** Return the format or NUll if error.
*/

t_format		*extract(char **str)
{
	t_format *format;

	if (!(format = new_format()))
		return (NULL);
	check_flags(str, &format);
	check_width(str, &((format)->min_width));
	check_period(str, &format);
	check_width(str, &((format)->precision));
	check_modifier(str, &format);
	check_type(str, &format);
	return (format);
}
