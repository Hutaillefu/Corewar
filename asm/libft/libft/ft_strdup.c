/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strdup.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: quruiz <quruiz@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/05 18:21:10 by quruiz       #+#   ##    ##    #+#       */
/*   Updated: 2018/05/12 16:52:55 by quruiz      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*cpy;

	if (s1 == NULL)
		return (NULL);
	i = ft_strlen(s1);
	if (!(cpy = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	cpy = ft_strcpy(cpy, s1);
	return (cpy);
}
