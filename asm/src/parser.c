/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parser.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: quruiz <quruiz@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/12 17:11:43 by quruiz       #+#   ##    ##    #+#       */
/*   Updated: 2019/03/23 21:04:58 by quruiz      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/asm.h"

int		parse_file(t_asm *env)
{
	char *line;

	if (!get_header(env))
		return (0);
	while (read_file(env, &line))
	{
		if (!get_cmd(env, line))
			return (ft_free_line(&line, 0));
		ft_strdel(&line);
	}
	if (!line)
		return (1);
	return (err_code(NEW_LINE, NULL, env));
}

char	*remove_comment(char *line)
{
	char	*comment;
	char	*tmp;

	if ((comment = ft_strchr(line, COMMENT_CHAR)))
	{
		tmp = ft_strsub(line, 0, comment - line);
		free(line);
		line = tmp;
	}
	if ((comment = ft_strchr(line, SECOND_COMMENT_CHAR)))
	{
		tmp = ft_strsub(line, 0, comment - line);
		free(line);
		line = tmp;
	}
	return (line);
}

int		read_file(t_asm *env, char **line)
{
	char	*tmp;
	int		ret;

	*line = NULL;
	ret = get_next_line(env->input_fd, line);
	env->line_nb++;
	if (ft_str_is_empty(*line) || **line == COMMENT_CHAR ||
		**line == SECOND_COMMENT_CHAR)
	{
		ft_strdel(line);
		return (ret ? read_file(env, line) : 0);
	}
	*line = remove_comment(*line);
	tmp = ft_strtrim(*line);
	free(*line);
	*line = tmp;
	return (ret);
}

int		get_cmd(t_asm *env, char *line)
{
	int decal;

	decal = get_label(env, line);
	if (decal == -1)
		return (0);
	while (ft_isnotprint(*(line + decal)))
		decal++;
	if (ft_str_is_empty(line + decal))
		return (1);
	if (!get_op(env, (line + decal)))
		return (0);
	return (1);
}
