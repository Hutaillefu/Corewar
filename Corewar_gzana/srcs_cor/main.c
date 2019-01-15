/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/09 15:04:49 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/15 13:44:07 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/corewar.h"


void	check_infos(t_cor *c)
{
	int i;

	i = -1;
	while (++i < c->vm->nb_player)
	{
		if (c->chmp[i]->champ_size > 682)
			ft_exit(3);
	}
}

int		main(int ac, char **av)
{
	t_cor *c;
	char *line;
	unsigned int len;

	c = ft_memalloc(sizeof(t_cor));
	init_vm(c, av, ac);
	read_infos(c, av);
	check_infos(c);
	init_map(c);
	print_map(c, 64);
	cycle(c);
	return (0);
}
