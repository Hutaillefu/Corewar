/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_add_line_to_tab.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: quruiz <quruiz@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/05 14:14:29 by quruiz       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/05 16:00:01 by quruiz      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	**ft_add_line_to_tab(char **tab, char *line, int size)
{
	char	**tmp;
	int		i;

	i = 0;
	if (!(tmp = ft_memalloc(sizeof(char *) * (size + 2))))
		return (0);
	while (i < size)
	{
		tmp[i] = tab[i];
		i++;
	}
	tmp[i] = line;
	tmp[i + 1] = NULL;
	if (size > 0)
		free(tab);
	return (tmp);
}
