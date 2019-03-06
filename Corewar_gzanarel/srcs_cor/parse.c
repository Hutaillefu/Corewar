/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/15 13:31:55 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/06 10:57:17 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/corewar.h"

int		check_num(t_cor *c, char **av, int i)
{
	int j;

	j = -1;
	if (!av[i])
		ft_exit(5);
	while (av[i][++j])
		if (ft_isalnum(av[i][j]) == 0)
			ft_exit(5);
	c->vm->num[c->vm->nb_player] = ft_atoi(av[i]);
	return (1);
}

int		check_dump(t_cor *c, char **av, int i)
{
	int j;

	j = -1;
	if (!av[i])
		ft_exit(5);
	while (av[i][++j])
		if (ft_isalnum(av[i][j]) == 0)
			ft_exit(5);
	c->vm->dump = ft_atoi(av[i]);
	return (1);
}

int     check_parse(t_cor *c, char **av, int ac)
{
	int i;
	char *tmp;
	int len;

	i = 1;
	if (ac < 2)
		ft_exit(1);
	while (av[i])
	{
		len = 0;
		if (!ft_strcmp(av[i], "-d"))
			i += check_dump(c, av, i + 1);
		else if (!ft_strcmp(av[i], "-n"))
			i += check_num(c, av, i + 1);
		else if (!ft_strcmp(av[i], "-v"))
			c->vm->verbose = 1;
		else if ((len = ft_strlen(av[i])) > 4)
		{
			tmp = ft_strsub(av[i], (len - 4), len);
			if (ft_strcmp(".cor", tmp))
				ft_exit(2);
			if (c->vm->nb_player < MAX_PLAYERS)
				c->vm->player[c->vm->nb_player++] = ft_strdup(av[i]);
		}
		else
			ft_exit(2);
		if (i < ac)
			i++;
		else
			break ;
	}
	return (0);
}
