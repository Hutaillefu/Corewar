/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cycle.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/15 13:36:11 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/15 13:36:45 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/corewar.h"

void	cycle(t_cor *c)
{
	int cycle;

	// printf("c->cycle_to_die: %d\n", c->cycle_to_die);
	while (c->cycle_to_die > 0)
	{
		// printf("C: %d\n", c->vm->cycle);
		// printf("CtD: %d\n", c->cycle_to_die);
		cycle = 0;
		while (++cycle <= c->cycle_to_die)
		{
			//exec processus
			c->vm->cycle++;
			if (cycle == c->cycle_to_die)
				c->cycle_to_die -= c->vm->cycle_delta;
		}
	}
}
