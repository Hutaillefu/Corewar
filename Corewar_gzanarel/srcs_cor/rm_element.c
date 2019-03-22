/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   rm_element.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/22 14:16:12 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/22 16:03:58 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/corewar.h"

static void	rm_element_head_tail(t_list2 **lst, t_node *proc)
{
	if (proc->num == (*lst)->head->num)
	{
		// free((*lst)->head);
		(*lst)->head = (*lst)->head->next;
		if ((*lst)->head)
			(*lst)->head->prev = NULL;
		(*lst)->len--;
		if ((*lst)->len == 1)
			(*lst)->head = (*lst)->tail;
	}
	else if (proc->num == (*lst)->tail->num)
	{
		// free((*lst)->tail);
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
		rm_element_head_tail(&(*lst), proc);
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
