/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/09 15:04:49 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/25 16:10:09 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/corewar.h"


void	check_infos(t_cor *c)
{
	int i;

	i = -1;
	while (++i < c->vm->nb_player)
		if (c->chmp[i]->champ_size > 682)
			ft_exit(3);
}

void		ft_print_winner(t_cor *c)
{
	int j;
	int last;
	int win;

	win = 0;
	j = -1;
	last = 0;
	while (++j < c->vm->nb_player)
	{
		if (c->chmp[j]->last_live >= last)
		{
			last = c->chmp[j]->last_live;
			win = j;
		}
	}
	ft_printf("last_live_chmp: %s : %d\n", c->chmp[win]->name, c->chmp[win]->last_live);
	ft_printf("Contestant %d, \"%s\", has won !\n", win + 1, c->chmp[win]->name);
}

int		main(int ac, char **av)
{
	t_cor *c;

	c = ft_memalloc(sizeof(t_cor));
	init_vm(c, av, ac);
	read_infos(c);
	check_infos(c);
	init_map(c);
	cycle(c);
	ft_printf("cycle: %d\n", c->vm->cycle);
	// for (int i = 0; i < c->vm->nb_player; i++)
	ft_print_winner(c);
	return (0);
}
