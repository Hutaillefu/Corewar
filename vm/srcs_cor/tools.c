/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/26 15:39:54 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/27 16:16:27 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/corewar.h"

t_node	*create_proc(t_cor *c, t_chmp *chmp, int i)
{
	t_node	*mll;
	int		j;

	j = -1;
	if (!(mll = (t_node *)malloc(sizeof(t_node))))
		return (NULL);
	mll->carry = 0;
	mll->pc = 0 + (MEM_SIZE / c->vm->nb_player) * i;
	mll->pc_b = mll->pc;
	mll->op_size = 0;
	mll->exec = 0;
	while (++j < REG_NUMBER)
		mll->reg[j] = 0;
	mll->reg[0] = chmp->num;
	mll->next = NULL;
	mll->prev = NULL;
	mll->last_live = 0;
	mll->lives = 0;
	mll->num = i + 1;
	return (mll);
}

t_node	*clone_proc(t_node *parent)
{
	t_node	*mll;
	int		j;

	j = -1;
	if (!(mll = (t_node *)malloc(sizeof(t_node))))
		return (NULL);
	init_param(mll);
	mll->carry = parent->carry;
	mll->pc = parent->pc;
	mll->pc_b = parent->pc_b;
	mll->op_size = 0;
	mll->exec = 0;
	while (++j < REG_NUMBER)
		mll->reg[j] = parent->reg[j];
	mll->next = NULL;
	mll->prev = NULL;
	mll->last_live = parent->last_live;
	mll->lives = parent->lives;
	return (mll);
}

void	add_element_end(t_list2 **lst, t_cor *c, t_chmp *chmp, int i)
{
	t_node *new;

	if (!lst || !(new = create_proc(c, chmp, i)))
		return ;
	if (!((*lst)->head))
	{
		(*lst)->head = new;
		(*lst)->tail = new;
	}
	else
	{
		(*lst)->head->prev = new;
		new->next = (*lst)->head;
		(*lst)->head = new;
	}
	(*lst)->len++;
}

void	push_back(t_list2 **lst, t_node *proc)
{
	if (!lst)
		return ;
	if (!((*lst)->tail))
	{
		(*lst)->head = proc;
		(*lst)->tail = proc;
	}
	else
	{
		(*lst)->tail->next = proc;
		proc->prev = (*lst)->tail;
	}
	(*lst)->nb++;
	(*lst)->len++;
}

void	push_front(t_list2 **lst, t_node *proc)
{
	if (!lst)
		return ;
	if (!((*lst)->head))
	{
		(*lst)->head = proc;
		(*lst)->tail = proc;
	}
	else
	{
		proc->prev = NULL;
		proc->next = (*lst)->head;
		(*lst)->head->prev = proc;
		(*lst)->head = proc;
	}
	(*lst)->nb++;
	(*lst)->len++;
}
