/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstdel.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: quruiz <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/05 18:21:03 by quruiz       #+#   ##    ##    #+#       */
/*   Updated: 2017/12/05 18:21:03 by quruiz      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*nxt_lst;
	t_list	*lst;

	lst = *alst;
	if (!alst || !del)
		return ;
	else
	{
		while (lst)
		{
			nxt_lst = lst->next;
			del(lst->content, lst->content_size);
			free(lst);
			lst = nxt_lst;
		}
	}
	*alst = NULL;
}
