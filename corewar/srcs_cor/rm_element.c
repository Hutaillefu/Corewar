/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   rm_element.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/22 18:55:44 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/26 13:35:49 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/corewar.h"

static void	rm_element_head_tail(t_list2 **lst, t_node *proc)
{
	if (proc->num == (*lst)->head->num)
	{
		(*lst)->head = (*lst)->head->next;
		if ((*lst)->head)
			(*lst)->head->prev = NULL;
		(*lst)->len--;
		if ((*lst)->len == 1)
			(*lst)->head = (*lst)->tail;
	}
	else if (proc->num == (*lst)->tail->num)
	{
		(*lst)->tail = (*lst)->tail->prev;
		if ((*lst)->tail)
			(*lst)->tail->next = NULL;
		(*lst)->len--;
		if ((*lst)->len == 1)
			(*lst)->head = (*lst)->tail;
	}
}

void		rm_element(t_list2 **lst, t_node *proc)
{
	t_node *tmp;

	if (!lst || !proc)
		return ;
	tmp = (*lst)->head;
	if (proc->num == (*lst)->head->num || proc->num == (*lst)->tail->num)
	{
		rm_element_head_tail(&(*lst), proc);
		free(proc);	
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
				free(proc);
				return ;
			}
			tmp = tmp->next;
		}
	}
}
