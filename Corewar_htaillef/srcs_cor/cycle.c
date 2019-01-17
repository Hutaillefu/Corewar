/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cycle.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/15 13:36:11 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/17 16:11:09 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/corewar.h"

void	cycle(t_cor *c)
{
	int cycle;
	int player;

	while (c->cycle_to_die > 0)
	{
		cycle = 0;
		while (++cycle <= c->cycle_to_die)
		{
			player = -1;
			while (++player < c->vm->nb_player)
			{
				if (c->chmp[player]->exec == c->vm->cycle)
					start_processus(c, c->chmp[player]);
				if (c->chmp[player]->exec == 0)
					if (exec_process(c->vm, c->chmp[player]) == 1)
						load_processus(c->vm->cycle, c->chmp[player]);
				// else
					// continue ;
			}
			if (c->vm->dump == c->vm->cycle)
				ft_flag_dump(c);
			c->vm->cycle++;
			if (cycle == c->cycle_to_die)
			{
				cycle = 0;
				c->cycle_to_die -= c->vm->cycle_delta;
			}
		}
	}
}
