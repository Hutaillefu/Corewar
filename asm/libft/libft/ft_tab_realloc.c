/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_tab_realloc.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: quruiz <quruiz@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/03 14:52:01 by quruiz       #+#   ##    ##    #+#       */
/*   Updated: 2018/05/04 18:07:22 by quruiz      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		*ft_tab_realloc(int *tab, int o, int n)
{
	int		*ntab;
	int		i;

	i = 0;
	if (o > n)
		return (NULL);
	if (!(ntab = malloc(sizeof(int) * n)))
		return (NULL);
	while (i < o)
	{
		ntab[i] = tab[i];
		i++;
	}
	while (i < n)
	{
		ntab[i] = 0;
		i++;
	}
	if (o > 0)
		free(tab);
	return (ntab);
}
