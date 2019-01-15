/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strsplit.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/23 14:25:05 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/27 12:09:21 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"

static	int	ft_count_word(char *s, char c)
{
	int i;
	int nb_word;

	nb_word = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			nb_word++;
			while (s[i] != c && s[i])
				i++;
		}
		if (s[i] != '\0')
			i++;
	}
	return (nb_word);
}

static	int	ft_len_word(char *s, char c)
{
	int i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**tab;
	int		i;
	int		wc;

	if (s == NULL || c == 0)
		return (0);
	wc = ft_count_word((char *)s, c);
	i = 0;
	tab = (char **)malloc(sizeof(char *) * (wc + 1));
	if (tab == NULL)
		return (NULL);
	while (wc--)
	{
		while (*s == c && *s != '\0')
			s++;
		if (*s != c && *s != '\0')
		{
			tab[i] = ft_strsub(s, 0, ft_len_word((char *)s, c));
			s = s + ft_len_word((char *)s, c);
			i++;
		}
	}
	tab[i] = 0;
	return (tab);
}
