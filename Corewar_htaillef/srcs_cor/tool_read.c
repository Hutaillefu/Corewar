/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tool_read.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/10 13:05:36 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/10 13:19:02 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/corewar.h"

static void	realloc_line(t_line *ln, int i)
{
	if (i >= ln->size)
	{
		ln->line = ft_realloc((void *)ln->line, ln->size, ln->size * 2);
		ln->size *= 2;
		if (ln->line == NULL)
			exit_err("Malloc error on line realloc");
	}
}

void		init_line(t_line *ln)
{
	ln->size = 256;
	ln->line = malloc(sizeof(char) * ln->size);
	if (ln->line == NULL)
		exit_err("Malloc error on line init");
}

int			readline(t_line *ln)
{
	int		i;
	char	buf[1];

	buf[0] = '\0';
	i = 0;
	if (read(0, buf, 1) <= 0)
		return (-1);
	while (buf[0] != '\n' && buf[0] != '\0')
	{
		ln->line[i] = buf[0];
		i++;
		realloc_line(ln, i);
		if (read(0, buf, 1) <= 0)
			break ;
	}
	ln->line[i] = '\0';
	if (iscomment(ln->line))
		readline(ln);
	return (is_special(ln->line));
}