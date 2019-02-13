/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cycle.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/15 13:36:11 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/13 16:08:23 by gzanarel    ###    #+. /#+    ###.fr     */
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
				(*lst)->len--;
			}
			else
			{ 
				printf("Remove first process of list P%d\n", proc->num);			
				(*lst)->head = tmp->next;
				if ((*lst)->head)
					(*lst)->head->prev = NULL;
				(*lst)->len--;			
			}
				return ;
			// free tmp
		}
		tmp = tmp->next;
	}
}

void		read_and_process(t_cor *c, t_node *tmp)
{
	exec_process(c->vm, tmp);
	if (c->vm->cycle == tmp->exec && start_processus(c, tmp))
		read_and_process(c, c->proc->head);
	if (tmp->exec == 0)
	{
		exec_process(c->vm, tmp);
		load_processus(c->vm->cycle, tmp);
	}
}

/*
  ** Return 1 if no more processus and prog should stop
*/
int	cycle_to_die(t_cor *c, int cycle, int *max)
{
	t_node *tmp;

	if (cycle == c->vm->cycle_to_die)
	{
		// Kills process unlive
		tmp = c->proc->head;
		while (tmp)
		{
			if (c->vm->cycle - tmp->last_live >= c->vm->cycle_to_die)
				rm_element(&(c->proc), tmp);
			if (!c->proc->head) // No process any more
				return (1);
			tmp = tmp->next;
		}
		if (c->vm->nb_live >= NBR_LIVE)
		{
			c->vm->cycle_to_die -= c->vm->cycle_delta;
			c->vm->nb_live = 0;
		}
		else
			(*max)++;
		cycle = 0;
	}
	if (*max == MAX_CHECKS)
		c->vm->cycle_to_die -= c->vm->cycle_delta;
	return (0);
}

void	cycle(t_cor *c)
{
	int		cycle;
	t_node	*tmp;
	int		max;

	max = 0;
	while (c->vm->cycle_to_die > 0)
	{
		cycle = 0;
		while (cycle++ <= c->vm->cycle_to_die)
		{
			ft_printf("It is now cycle %d || CTD: %d\n", c->vm->cycle, c->vm->cycle_to_die);
			if (c->vm->dump == c->vm->cycle)
				ft_flag_dump(c);
			tmp = c->proc->head;
			while (tmp)
			{
				read_and_process(c, tmp);
				tmp = tmp->next;
			}
			if (cycle_to_die(c, cycle, &max))
				return ;
			c->vm->cycle++;
		}
	}
}