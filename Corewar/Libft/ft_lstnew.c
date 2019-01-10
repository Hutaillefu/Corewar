/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstnew.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/23 14:15:09 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/11 15:37:14 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *newlst;

	newlst = malloc(sizeof(t_list));
	if (newlst == 0)
		return (NULL);
	if (content == 0)
	{
		newlst->content = NULL;
		newlst->content_size = 0;
	}
	else
	{
		newlst->content = malloc(sizeof(content) * content_size);
		if (newlst->content == 0)
			return (NULL);
		ft_memcpy(newlst->content, content, content_size);
		newlst->content_size = content_size;
	}
	newlst->next = NULL;
	return (newlst);
}
