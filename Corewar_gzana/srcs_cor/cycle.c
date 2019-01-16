/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cycle.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/15 13:36:11 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/16 14:37:46 by gzanarel    ###    #+. /#+    ###.fr     */
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
				printf("c->chmp[%d]->exec: %d || cycle: %d || pc %d\n", player, c->chmp[player]->exec, c->vm->cycle, c->chmp[player]->pc);
				if (c->chmp[player]->exec == 0)
				{
					printf("enter\n");
					if (exec_process(c->vm, c->chmp[player]) == 1)
					{
						load_processus(c->vm->cycle, c, c->chmp[player]);
					}
				}
				else if (c->chmp[player]->exec == c->vm->cycle)
				{
					start_processus(c->chmp[player], c->vm);
				}
				else
					continue ;
			}
			if (c->vm->dump == c->vm->cycle)
			{
				print_map(c, 64);
				exit(0);
			}
			c->vm->cycle++;
			if (cycle == c->cycle_to_die)
			{
				cycle = 0;
				c->cycle_to_die -= c->vm->cycle_delta;
			}
		}
	}
}
