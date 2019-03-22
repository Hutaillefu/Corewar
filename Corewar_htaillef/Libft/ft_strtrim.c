/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strtrim.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/23 14:25:45 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/11 15:40:42 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strtrim(char const *s)
{
	int		i;
	char	*trim;
	int		len;
	int		size_s;

	if (s == NULL)
		return (NULL);
	size_s = ft_strlen1((char *)s);
	i = 0;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	while ((s[size_s - 1] == ' ' || s[size_s - 1] == '\n' ||
				s[size_s - 1] == '\t') && ((size_s - 1) > 0) && i < size_s)
		size_s--;
	len = size_s - i;
	trim = (char *)malloc(sizeof(char) * len + 1);
	if (trim != NULL)
	{
		trim = ft_strsub((char *)s, i, len);
		trim[len] = '\0';
	}
	return (trim);
}
