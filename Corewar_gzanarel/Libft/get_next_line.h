/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.h                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/06 13:00:54 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/19 16:36:10 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 10

# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include "includes/libft.h"

typedef	struct	s_get
{
	int			fd;
	char		*save;
	int			count;
}				t_get;

int				get_next_line(const int fd, char **line);
int				read_nl(int fd, char ***line, t_get **get);
int				ft_malloc_cpy(char *buf, t_get ***get);
int				ft_create_line(t_get ***get, char ****line);
int				ft_strlen_ext(char *str, int c);

#endif
