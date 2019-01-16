/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstmap.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/23 14:14:53 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/11 15:37:08 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *start;
	t_list *tmp;
	t_list *nlist;

	if (lst == NULL)
		return (NULL);
	tmp = f(lst);
	start = ft_lstnew(tmp->content, tmp->content_size);
	if (start == NULL)
		return (NULL);
	nlist = start;
	lst = lst->next;
	while (lst)
	{
		tmp = f(lst);
		start->next = ft_lstnew(tmp->content, tmp->content_size);
		lst = lst->next;
		start = start->next;
	}
	return (nlist);
}
