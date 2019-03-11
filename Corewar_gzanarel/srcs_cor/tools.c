/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/26 15:39:54 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/11 12:12:42 by gzanarel    ###    #+. /#+    ###.fr     */
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
	if (!((*lst)->tail))
	{
		(*lst)->head = new;
		(*lst)->tail = new;
	}
	else
	{
		(*lst)->tail->next = new;
		new->prev = (*lst)->tail;
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


// void	del_element_end(t_list2 *lst)
// {
// 	t_node *tmp;

// 	tmp = lst->tail;
// 	if (lst != NULL)
// 	{
// 		lst->tail = lst->tail->prev;
// 		lst->tail->next = NULL;
// 	}
// 	(lst)->len--;
// 	free(tmp);
// }

// void	del_element_head(t_list2 *lst)
// {
// 	t_node *tmp;

// 	tmp = lst->head;
// 	if (tmp->next == NULL && tmp->prev == NULL)
// 	{
// 		lst->head = NULL;
// 		lst->tail = NULL;
// 	}
// 	else if (tmp->next == NULL)
// 	{
// 		lst->tail = tmp->prev;
// 		lst->tail->next = NULL;
// 	}
// 	else if (tmp->prev == NULL)
// 	{
// 		lst->head = tmp->next;
// 		lst->head->prev = NULL;
// 	}
// 	else
// 	{
// 		tmp->next->prev = tmp->prev;
// 		tmp->prev->next = tmp->next;
// 	}
// 	lst->len--;
// 	tmp = NULL;
// 	free(tmp);
// }

// void	add_element_head(t_list2 *lst, int v)
// {
// 	t_node *new;

// 	new = create_list(v);
// 	if (lst->head == NULL)
// 	{
// 		new->next = NULL;
// 		lst->head = new;
// 		lst->tail = new;
// 	}
// 	else
// 	{
// 		lst->head->prev = new;
// 		new->next = lst->head;
// 		lst->head = new;
// 	}
// 	lst->len++;
// }

// int		ft_lstlenght(t_node *p)
// {
// 	int i;

// 	i = 0;
// 	while (p)
// 	{
// 		p = p->next;
// 		i++;
// 	}
// 	return (i);
// }

// void	view(t_list2 *lst)
// {
// 	t_node *p;

// 	p = lst->head;
// 	while (p)
// 	{
// 		ft_printf("[%d](ID: %d)\n", p->nb, p->id);
// 		p = p->next;
// 	}
// 	ft_printf("\n");
// }

// void	new_list(t_list2 *lst)
// {
// 	if (lst == malloc(sizeof(t_list2)))
// 	{
// 		lst->len = 0;
// 		lst->head = NULL;
// 		lst->tail = NULL;
// 	}
// }