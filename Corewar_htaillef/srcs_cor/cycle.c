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

void	rm_element(t_list2 **lst, t_node *proc)
{
	t_node *tmp;

	if (!lst || !proc)
		return ;
	tmp = (*lst)->head;
	while (tmp)
	{
		if (tmp->num == proc->num)
		{
			if (tmp->prev)
			{
				printf("Remove process of list P%d\n", proc->num);								
				tmp->prev->next = tmp->next;
			}
			else
			{ 
				printf("Remove first process of list P%d\n", proc->num);			
				(*lst)->head = tmp->next;
				if ((*lst)->head)
					(*lst)->head->prev = NULL;
			}
				return ;
			// free tmp
		}
		tmp = tmp->next;
	}
}

void	cycle(t_cor *c)
{
	int cycle;
	t_node *tmp;
	int max;

	max = 0;
	while (c->vm->cycle_to_die > 0)
	{
		cycle = 0;
		while (++cycle <= c->vm->cycle_to_die)
		{
			tmp = c->proc->head;
			c->vm->cycle++;
			
			while (tmp)
			{
				if (tmp->exec == 0 && exec_process(c->vm, tmp) == 1)
						load_processus(c->vm->cycle, tmp);
				else if (tmp->exec == c->vm->cycle && c->vm->cycle > 0)
					start_processus(c, tmp);
				tmp = tmp->next;
			}
			if (c->vm->dump == c->vm->cycle)
				ft_flag_dump(c);
			//c->vm->cycle++;
			if (cycle == c->vm->cycle_to_die)
			{
				// Kills process unlive
				tmp = c->proc->head;
				while (tmp)
				{
					if (cycle - tmp->last_live >= c->vm->cycle_to_die)
						rm_element(&(c->proc), tmp);
					if (!c->proc->head) // No process any more
						return ;
					tmp = tmp->next;
				}

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
