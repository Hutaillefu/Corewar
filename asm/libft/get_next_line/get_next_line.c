/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: quruiz <quruiz@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/14 12:45:05 by quruiz       #+#   ##    ##    #+#       */
/*   Updated: 2019/03/02 19:49:55 by quruiz      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"

static t_gnl		*get_fd(t_gnl **file_fd, const int fd)
{
	t_gnl	*tmp;

	tmp = *file_fd;
	while (tmp)
	{
		if (tmp->fd == fd)
			return (tmp);
		tmp = tmp->next;
	}
	tmp = (t_gnl *)malloc(sizeof(t_gnl));
	tmp->s = ft_strnew(0);
	tmp->fd = fd;
	tmp->next = *file_fd;
	*file_fd = tmp;
	return (tmp);
}

static char			*get_line(t_gnl *list)
{
	char		*str;
	char		*tmp;
	size_t		i;

	i = 0;
	while (list->s[i] != '\n' && list->s[i] != '\0')
		i++;
	list->ret = (list->s[i] == '\n' ? 1 : 0);
	str = (char *)malloc(sizeof(char) * i + 1);
	str[i] = '\0';
	i = 0;
	while (list->s[i] != '\n' && list->s[i] != '\0')
	{
		str[i] = list->s[i];
		i++;
	}
	if (i < ft_strlen(list->s))
	{
		tmp = list->s;
		list->s = ft_strsub(list->s, i + 1, (ft_strlen(list->s) - (i + 1)));
		free(tmp);
	}
	else
		ft_strclr(list->s);
	return (str);
}

int					get_next_line(const int fd, char **line)
{
	static t_gnl	*file_fd;
	t_gnl			*list;
	char			*tmp;
	char			buf[BUFF_SIZE + 1];
	size_t			ret;

	tmp = NULL;
	if (fd < 0 || line == NULL || BUFF_SIZE < 1 || read(fd, buf, 0) == -1)
		return (-1);
	list = get_fd(&file_fd, fd);
	list->ret = 0;
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		buf[ret] = '\0';
		tmp = list->s;
		list->s = ft_strjoin(list->s, buf);
		free(tmp);
		if (ft_strchr(list->s, '\n'))
			break ;
	}
	if (ft_strlen(list->s))
		*line = get_line(list);
	return (list->ret);
}
