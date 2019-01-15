/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/06 13:00:36 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/19 16:36:07 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_strlen_ext(char *str, int c)
{
	int i;

	i = 0;
	while (str[i] != c && str[i])
		i++;
	return (i);
}

int		ft_create_line(t_get ***get, char ****line)
{
	int		len;
	char	*tmp;

	len = ft_strlen_ext((**get)->save, '\n');
	if (!(***line = ft_strnew(len)))
		return (-1);
	***line = ft_strncpy(***line, (**get)->save, len);
	if ((tmp = ft_strsub((**get)->save, (len + 1), (**get)->count)) == NULL)
		return (-1);
	(**get)->count -= len + 1;
	ft_strdel(&((**get)->save));
	if (tmp[0] != '\0')
		if (!((**get)->save = ft_strdup(tmp)))
			return (-1);
	ft_strdel(&tmp);
	return (1);
}

int		ft_malloc_cpy(char *buf, t_get ***get)
{
	char	*tmp;

	if (!((**get)->save))
	{
		if (!((**get)->save = ft_strdup(buf)))
			return (-1);
	}
	else
	{
		if (!(tmp = ft_strjoin(((**get)->save), buf)))
			return (-1);
		ft_strdel(&((**get)->save));
		if (!((**get)->save = ft_strdup(tmp)))
			return (-1);
		ft_strdel(&tmp);
	}
	return (1);
}

int		read_nl(int fd, char ***line, t_get **get)
{
	int			rd;
	char		buf[BUFF_SIZE + 1];

	rd = 0;
	while ((rd = read(fd, &buf, BUFF_SIZE)))
	{
		if (rd < 0)
			return (-1);
		buf[rd] = '\0';
		(*get)->count += rd;
		if ((ft_malloc_cpy(buf, &get)) == -1)
			return (-1);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	if ((*get)->count > 0)
		return (ft_create_line(&get, &line));
	else
	{
		ft_strdel(&((*get)->save));
		free(*get);
		*get = NULL;
		return (0);
	}
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	int				ret;
	static t_get	*get;

	if (get == NULL || get->fd != fd)
	{
		if (!(get = malloc(sizeof(t_get))))
			return (-1);
		get->save = NULL;
		get->count = 0;
		get->fd = fd;
	}
	if (fd < 0)
		return (-1);
	ret = read_nl(fd, &line, &get);
	return (ret);
}
