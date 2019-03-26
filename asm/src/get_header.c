/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_header.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: quruiz <quruiz@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/31 21:00:46 by quruiz       #+#   ##    ##    #+#       */
/*   Updated: 2019/03/24 00:33:31 by quruiz      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/asm.h"

char	*read_more(t_asm *env, char **line, char *cmd, int limit)
{
	char	*tmp;
	int		len[3];

	len[0] = ft_strlen(*line);
	len[1] = ft_strlen(ft_strchr(*line, '"') + 1);
	while (get_next_line(env->input_fd, &tmp))
	{
		env->line_nb++;
		len[2] = ft_strlen(tmp);
		*line = ft_conncat(*line, "\n", len[0], 1);
		*line = ft_conncat(*line, tmp, len[0] + 1, len[2]);
		len[2]++;
		len[0] += len[2];
		len[1] += len[2];
		free(tmp);
		if (len[1] > limit)
		{
			free(*line);
			return (err_code(SIZE_ERROR, cmd, env) ? NULL : NULL);
		}
		if (ft_strchr((*line + (len[0] - len[2])), '"'))
			return (*line);
	}
	free(*line);
	return (err_code(SYNTAX_ERROR, cmd, env) ? NULL : NULL);
}

int		parse_name(t_asm *env, char **line, char *dest)
{
	char	*start;
	char	*end;
	int		cmd_size;

	cmd_size = ft_strlen(NAME_CMD_STRING);
	if (!(start = ft_strnstr(*line, NAME_CMD_STRING, cmd_size)))
		return (err_code(NO_TOKEN, NAME_CMD_STRING, env));
	start += cmd_size;
	while (!ft_isprint(*start))
		start++;
	if (*start != '"')
		return (err_code(SYNTAX_ERROR, NAME_CMD_STRING, env));
	if (!(end = ft_strchr(start + 1, '"')))
	{
		if (!(*line = read_more(env, line, NAME_CMD_STRING, PROG_NAME_LENGTH)))
			return (0);
		return (parse_name(env, line, dest));
	}
	else if (!ft_str_is_empty(end + 1))
		return (err_code(SYNTAX_ERROR, NAME_CMD_STRING, env));
	if ((end - (start + 1)) > PROG_NAME_LENGTH)
		return (err_code(SIZE_ERROR, NAME_CMD_STRING, env));
	ft_strncpy(dest, (start + 1), (end - (start + 1)));
	return (1);
}

int		parse_comment(t_asm *env, char **line, char *dest)
{
	char	*start;
	char	*end;
	int		cmd_size;

	cmd_size = ft_strlen(COMMENT_CMD_STRING);
	if (!(start = ft_strnstr(*line, COMMENT_CMD_STRING, cmd_size)))
		return (err_code(NO_TOKEN, COMMENT_CMD_STRING, env));
	start += cmd_size;
	while (!ft_isprint(*start))
		start++;
	if (*start != '"')
		return (err_code(SYNTAX_ERROR, COMMENT_CMD_STRING, env));
	if (!(end = ft_strchr(start + 1, '"')))
	{
		if (!(*line = read_more(env, line, COMMENT_CMD_STRING, COMMENT_LENGTH)))
			return (0);
		return (parse_comment(env, line, dest));
	}
	else if (!ft_str_is_empty(end + 1))
		return (err_code(SYNTAX_ERROR, COMMENT_CMD_STRING, env));
	if ((end - (start + 1)) > COMMENT_LENGTH)
		return (err_code(SIZE_ERROR, COMMENT_CMD_STRING, env));
	ft_strncpy(dest, (start + 1), (end - (start + 1)));
	return (1);
}

int		get_header(t_asm *env)
{
	int		i;
	char	*line;

	i = 0;
	ft_bzero(&env->header, sizeof(t_header));
	env->header.magic = ft_bswap_int32(COREWAR_EXEC_MAGIC);
	while (i < 2)
	{
		if (read_file(env, &line))
		{
			if (!i && !parse_name(env, &line, env->header.prog_name))
				return (ft_free_line(&line, 0));
			if (i && !parse_comment(env, &line, env->header.comment))
				return (ft_free_line(&line, 0));
		}
		else
		{
			ft_strdel(&line);
			return (err_code(SYNTAX_ERROR, NULL, env));
		}
		ft_strdel(&line);
		i++;
	}
	return (1);
}
