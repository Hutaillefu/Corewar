/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strdup.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/23 14:21:17 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/11 15:39:15 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strdup(const char *s1)
{
	char	*src;
	char	*dup;
	int		lenght;
	int		i;

	i = 0;
	src = (char *)s1;
	lenght = ft_strlen(src);
	if (lenght == 0)
		src = NULL;
	dup = (char *)malloc(sizeof(char) * (lenght + 1));
	if (dup != NULL)
	{
		while (i < lenght)
		{
			dup[i] = src[i];
			i++;
		}
		dup[i] = '\0';
	}
	return (dup);
}
