/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cycle.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/15 13:36:11 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/12 18:15:12 by gzanarel    ###    #+. /#+    ###.fr     */
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
	
	// while (tmp)
	// {
	// 	if (tmp->num == proc->num)
	// 	{
	// 		if (tmp->prev)
	// 		{
	// 			//printf("Remove process of list P%d\n", proc->num);								
	// 			tmp = tmp->prev;
	// 			stk = tmp->next;
	// 			tmp = tmp->next;
	// 			tmp->prev->next = tmp->next;
	// 			(*lst)->len--;
	// 		}
	// 		else
	// 		{ 
	// 			//printf("Remove first process of list P%d\n", proc->num);			
	// 			(*lst)->head = tmp->next;
	// 			if ((*lst)->head)
	// 				(*lst)->head->prev = NULL;
	// 			(*lst)->len--;			
	// 		}
	// 			return ;
	// 		// free tmp
	// 	}
	// 	tmp = tmp->next;
	// }
}

void		read_and_process(t_cor *c, t_node *tmp)
{
	if ((c->vm->cycle == tmp->exec && tmp->exec != 0))
	{
		exec(c->vm, tmp);
		if (c->vm->cycle == tmp->exec && start_processus(c, tmp))
			read_and_process(c, c->proc->head);
	}
	// if (tmp->exec == 0)
	// {
	// 	load(c->vm, tmp);
	// 	load_processus(c->vm->cycle, tmp);
	// }
}

void		read_and_process1(t_cor *c, t_node *tmp)
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
		//printf("cycle %d\n", cycle);
		// Kills process unlive
		tmp = c->proc->head;
		while (tmp)
		{
			if (c->vm->cycle - tmp->last_live >= c->vm->cycle_to_die)
			{
				if (c->vm->verbose & V_DEATH)
					ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n", tmp->num, c->vm->cycle - tmp->last_live, c->vm->cycle_to_die);
				rm_element(&(c->proc), tmp);
			}
			if (!c->proc->head) // No process any more
				return (1);
			tmp = tmp->next;
		}
		if (c->vm->max_chk >= MAX_CHECKS)
		{
			// c->vm->nb_live = 0;
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
			// c->vm->nb_live = 0;
			c->vm->max_chk = 1;
		}
		cycle = 0;
		c->vm->nb_live = 0;
	}
	return (0);
}

void	cycle(t_cor *c)
{
	int		cycle;
	t_node	*tmp;
	// int		max;

	cycle = -1;
	// max = 0;
	while (c->vm->cycle_to_die > 0 && c->proc->head)
	{
		if (cycle > 0)
			cycle = 0;
		while (++cycle <= c->vm->cycle_to_die)
		{
			if (c->vm->cycle > 0 && (c->vm->verbose & V_CYCLE))
				ft_printf("It is now cycle %d\n", c->vm->cycle);

			// Exec
			tmp = c->proc->head;
			while (tmp)
			{
				read_and_process(c, tmp);
				tmp = tmp->next;
			}

			// Load
			tmp = c->proc->head;
			while (tmp)
			{
				read_and_process1(c, tmp);
				tmp = tmp->next;
			}
			if (c->vm->dump == c->vm->cycle)
				ft_flag_dump(c);
			cycle_to_die(c, cycle);
			c->vm->cycle++;
			if (c->vm->cycle_to_die <= 0)
			{
				if (c->vm->verbose & V_CYCLE)
					ft_printf("It is now cycle %d\n", c->vm->cycle);				
				tmp = c->proc->head;
				while (tmp)
				{
					read_and_process(c, tmp);
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
