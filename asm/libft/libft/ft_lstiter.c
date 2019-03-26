/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstiter.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: quruiz <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/05 18:21:03 by quruiz       #+#   ##    ##    #+#       */
/*   Updated: 2017/12/05 18:21:03 by quruiz      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(t_list *elem))
{
	t_list	*idx_lst;
	t_list	*nxt_lst;

	idx_lst = lst;
	if (!lst || !f)
		return ;
	else
	{
		while (idx_lst)
		{
			nxt_lst = idx_lst->next;
			f(idx_lst);
			idx_lst = nxt_lst;
		}
	}
}
