/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/15 13:31:55 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/15 13:45:28 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/corewar.h"

int     check_parse(t_cor *c, char **av, int ac)
{
	int i;
	int fd;
	char *tmp;

	i = 1;
	if (ac < 2 || ac > MAX_ARGS_NUMBER + 1)
		ft_exit(1);
	while (av[i])
	{

		if (!ft_strcmp(av[i], "-d"))
			printf("flag d\n"); // rajout recup flag -d
		else if (!ft_strcmp(av[i], "-n"))
			printf("flag n\n"); // rajout recup flag -n
		else if (ft_strlen(av[i]) > 4)
		{
			tmp = ft_strsub(av[i], (ft_strlen(av[i]) - 4), ft_strlen(av[i]));
			if (ft_strcmp(".cor", tmp))
				ft_exit(2);
			if (c->vm->nb_player < 4)
				c->vm->player[c->vm->nb_player++] = ft_strdup(av[i]);
		}
		if (i < ac)
			i++;
		else
			break ;
	}
	return (0);
}
