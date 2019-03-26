/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_freesplit.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: quruiz <quruiz@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/13 14:01:56 by quruiz       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/11 01:32:47 by quruiz      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		ft_freesplit(char **split)
{
	int		i;

	i = 0;
	if (!split)
		return (0);
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	split = NULL;
	return (0);
}
