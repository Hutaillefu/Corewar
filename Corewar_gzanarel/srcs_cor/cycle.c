/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cycle.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/15 13:36:11 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/13 15:32:36 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/corewar.h"

void	rm_element(t_list2 **lst, t_node *proc)
{
	t_node *tmp;
	tmp = (*lst)->head;

	if (!lst || !proc)
		return ;
	if (proc->num == (*lst)->head->num)
	{
		(*lst)->head = (*lst)->head->next;
		if ((*lst)->head)
			(*lst)->head->prev = NULL;
		(*lst)->len--;
		if ((*lst)->len == 1)
			(*lst)->head = (*lst)->tail;
		// free(tmp);
	}
	else if (proc->num == (*lst)->tail->num)
	{
		(*lst)->tail = (*lst)->tail->prev;
		if ((*lst)->tail)
			(*lst)->tail->next = NULL;
		// free(tmp);
		(*lst)->len--;
		if ((*lst)->len == 1)
			(*lst)->head = (*lst)->tail;
	}
	else
	{
		while (tmp)
		{
			if (tmp->num == proc->num)
			{

				tmp->prev->next = tmp->next;
				tmp->next->prev = tmp->prev;
				(*lst)->len--;
				// free(tmp);
				return ;
			}
			tmp = tmp->next;
		}
	}
}

static void		read_and_exec(t_cor *c, t_node *tmp)
{
	if ((c->vm->cycle == tmp->exec && tmp->exec != 0))
	{
		exec(c->vm, tmp);
		if (c->vm->cycle == tmp->exec && start_processus(c, tmp))
			read_and_exec(c, c->proc->head);
	}
}

static void		read_and_load(t_cor *c, t_node *tmp)
{
	if (tmp->exec == 0)
	{
		load(c->vm, tmp);
		load_processus(c->vm->cycle, tmp);
	}
}

/*
  ** Return 1 if no more processus and prog should stop
*/
int	cycle_to_die(t_cor *c, int cycle)
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
					ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n", tmp->num, c->vm->cycle - tmp->last_live, c->vm->cycle_to_die);
				rm_element(&(c->proc), tmp);
			}
			if (!c->proc->head)
				break ;
			tmp = tmp->next;
		}
		if (c->vm->max_chk >= MAX_CHECKS)
		{
			c->vm->max_chk = 1;
			c->vm->cycle_to_die -= c->vm->cycle_delta;
			if (c->vm->verbose & V_CYCLE)
				ft_printf("Cycle to die is now %d\n", c->vm->cycle_to_die);
		}
		else
			c->vm->max_chk++;
		if (c->vm->nb_live >= NBR_LIVE)
		{
			c->vm->cycle_to_die -= c->vm->cycle_delta;
			if (c->vm->verbose & V_CYCLE)
				ft_printf("Cycle to die is now %d\n", c->vm->cycle_to_die);
			c->vm->max_chk = 1;
		}
		cycle = 0;
		c->vm->nb_live = 0;
	}
	return (cycle);
}

void	cycle(t_cor *c)
{
	int		cycle;
	t_node	*tmp;

	cycle = -1;
	while (c->vm->cycle_to_die > 0 && c->proc->head)
	{
		if (cycle > 0)
			cycle = 0;
		while (++cycle <= c->vm->cycle_to_die && c->proc->head)
		{
			if (c->vm->cycle > 0 && (c->vm->verbose & V_CYCLE))
				ft_printf("It is now cycle %d\n", c->vm->cycle);
			tmp = c->proc->head;
			while (tmp)
			{
				read_and_exec(c, tmp);
				tmp = tmp->next;
			}
			tmp = c->proc->head;
			while (tmp)
			{
				read_and_load(c, tmp);
				tmp = tmp->next;
			}
			// while (tmp)
			// {
			// 	read_and_exec(c, tmp);
			// 	read_and_load(c, tmp);
			// 	tmp = tmp->next;
			// }
			if (c->vm->dump == c->vm->cycle)
				ft_flag_dump(c);
			cycle = cycle_to_die(c, cycle);
			c->vm->cycle++;
			if (c->vm->cycle_to_die <= 0)
			{
				if (c->vm->verbose & V_CYCLE)
					ft_printf("It is now cycle %d\n", c->vm->cycle);				
				tmp = c->proc->head;
				while (tmp)
				{
					read_and_exec(c, tmp);
					tmp = tmp->next;
				}
				tmp = c->proc->head;
				while (tmp)
				{
					if (c->vm->verbose & V_DEATH)
						ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n", tmp->num, c->vm->cycle - tmp->last_live, c->vm->cycle_to_die);
					rm_element(&(c->proc), tmp);
					tmp = tmp->next;
				}
				return ;
			}
		}
	}
}
