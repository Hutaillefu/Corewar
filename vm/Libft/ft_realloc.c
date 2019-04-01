/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_realloc.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/10 13:07:02 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/10 13:07:16 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *tmp;

	tmp = malloc(new_size);
	if (tmp != NULL && ptr != NULL && old_size > 0)
	{
		if (new_size > old_size)
			ft_memcpy(tmp, ptr, old_size);
		else
			ft_memcpy(tmp, ptr, new_size);
	}
	if (ptr != NULL)
		free(ptr);
	return (tmp);
}
