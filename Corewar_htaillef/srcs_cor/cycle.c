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

void	ft_check_cycle(t_cor *c)
{
	if (c->vm->nb_live >= NBR_LIVE)
		c->vm->cycle_to_die -= c->vm->cycle_delta;
}

void	cycle(t_cor *c)
{
	int cycle;
	t_node *tmp;
	int max;

	max = 0;
	tmp = c->proc->head;
	while (c->vm->cycle_to_die > 0)
	{
		cycle = 0;
		while (++cycle <= c->vm->cycle_to_die)
		{
			while (tmp->next)
			{
				if (tmp->exec == c->vm->cycle)
					start_processus(c, tmp);
				if (tmp->exec == 0)
					if (exec_process(c->vm, tmp) == 1)
						load_processus(c->vm->cycle, tmp);
				tmp = tmp->next;
			}
			if (c->vm->dump == c->vm->cycle)
				ft_flag_dump(c);
			c->vm->cycle++;
			if (cycle == c->vm->cycle_to_die)
			{
				if (c->vm->nb_live >= NBR_LIVE)
					c->vm->cycle_to_die -= c->vm->cycle_delta;
				else
					max++;
				cycle = 0;
			}
			if (max == MAX_CHECKS)
				c->vm->cycle_to_die -= c->vm->cycle_delta;
		}
	}
}
