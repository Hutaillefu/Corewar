/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_label.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: quruiz <quruiz@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/31 20:59:29 by quruiz       #+#   ##    ##    #+#       */
/*   Updated: 2019/03/19 17:56:12 by quruiz      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/asm.h"

int		check_label_chars(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (ft_strchr(LABEL_CHARS, str[i]))
			i++;
		else
			break ;
	}
	if (str[i] == LABEL_CHAR)
		return (1);
	return (0);
}

int		get_label(t_asm *env, char *line)
{
	char	*tmp;
	t_code	*new;

	if (!check_label_chars(line))
		return (0);
	tmp = ft_strchr(line, LABEL_CHAR);
	if (!(new = ft_memalloc(sizeof(t_code))))
		return (err_code(MEM_ERROR, NULL, env) ? -1 : -1);
	new->type = 1;
	new->line_nb = env->line_nb;
	new->token = ft_strsub(line, 0, (tmp - line));
	new->next = NULL;
	add_to_list(env, new);
	return ((tmp + 1) - line);
}
