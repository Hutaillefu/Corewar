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
	int i;

	max = 0;
	while (c->vm->cycle_to_die > 0)
	{
		cycle = 0;
		while (++cycle <= c->vm->cycle_to_die)
		{
			tmp = c->proc->head;
			i =0;
			while (tmp)
			{
				if (tmp->exec == 0 && exec_process(c->vm, tmp) == 1)
						load_processus(c->vm->cycle, tmp);
				else if (tmp->exec == c->vm->cycle && c->vm->cycle > 0)
				{	
					printf("Start instruction of P%d\n", i);
					start_processus(c, tmp);
				}
				tmp = tmp->next;
				i++;
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
