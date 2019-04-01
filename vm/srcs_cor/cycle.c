/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cycle.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/15 13:36:11 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/27 15:18:35 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/corewar.h"

static void	read_and_load(t_cor *c, t_node *tmp, int i)
{
	if (!tmp->exec)
	{
		load(c->vm, tmp);
		load_processus(c->vm->cycle, tmp, i);
	}
}

static void	read_and_exec(t_cor *c, t_node *tmp)
{
	if ((c->vm->cycle >= tmp->exec && tmp->exec != 0))
	{
		exec(c->vm, tmp);
		start_processus(c, tmp);
	}
}

static void	read_proc(t_cor *c, t_node *tmp)
{
	while (tmp)
	{
		if (tmp->exec >= c->vm->cycle && c->vm->cycle != 0)
			read_and_exec(c, tmp);
		else if (!(c->vm->cycle))
			read_and_load(c, tmp, 0);
		else
			read_and_load(c, tmp, 1);
		if (tmp->op.opcode == -1 || tmp->op.opcode == 0)
			read_and_exec(c, tmp);
		tmp = tmp->next;
	}
}

void		cycle(t_cor *c)
{
	int		cycle;
	t_node	*tmp;

	cycle = 0;
	while (c->vm->cycle_to_die > 0 && c->proc->head)
	{
		if (c->vm->cycle > 0 && (c->vm->verbose & V_CYCLE))
			ft_printf(&(c->vm->logs), "It is now cycle %d\n", c->vm->cycle);
		tmp = c->proc->head;
		read_proc(c, tmp);
		if (c->vm->dump == c->vm->cycle)
			ft_flag_dump(c);
		cycle = cycle_to_die(c, cycle);
		c->vm->cycle++;
		cycle++;
	}
	if (c->vm->cycle_to_die < 0 && (c->vm->verbose & V_CYCLE) && c->proc->head)
		ft_printf(&(c->vm->logs), "It is now cycle %d\n", c->vm->cycle);
	read_proc(c, c->proc->head);
	cycle_to_die(c, cycle);
}
