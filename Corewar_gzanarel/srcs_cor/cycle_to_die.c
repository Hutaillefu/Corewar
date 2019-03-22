/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cycle_to_die.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/22 13:35:54 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/22 15:28:58 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/corewar.h"

static void	nbr_lives(t_cor *c)
{
	c->vm->cycle_to_die -= c->vm->cycle_delta;
	if (c->vm->verbose & V_CYCLE)
		ft_printf(&(c->vm->logs), "Cycle to die is now %d\n",
		c->vm->cycle_to_die);
	c->vm->max_chk = 1;
}

static void	nbr_checks(t_cor *c)
{
	c->vm->max_chk = 1;
	c->vm->cycle_to_die -= c->vm->cycle_delta;
	if (c->vm->verbose & V_CYCLE)
		ft_printf(&(c->vm->logs), "Cycle to die is now %d\n",
		c->vm->cycle_to_die);
}

int			cycle_to_die(t_cor *c, int cycle)
{
	t_node *tmp;

	if (cycle == c->vm->cycle_to_die)
	{
		tmp = c->proc->head;
		while (tmp)
		{
			if (c->vm->cycle - tmp->last_live >= c->vm->cycle_to_die)
			{
				if (c->vm->verbose & V_DEATH)
					ft_printf(&(c->vm->logs),
	"Process %d hasn't lived for %d cycles (CTD %d)\n",
	tmp->num, c->vm->cycle - tmp->last_live, c->vm->cycle_to_die);
				rm_element(&(c->proc), tmp);
			}
			tmp = tmp->next;
		}
		c->vm->max_chk >= MAX_CHECKS ? nbr_checks(c) : c->vm->max_chk++;
		c->vm->nb_live >= NBR_LIVE ? nbr_lives(c) : 0;
		cycle = 0;
		c->vm->nb_live = 0;
		free(tmp);
	}
	return (cycle);
}
