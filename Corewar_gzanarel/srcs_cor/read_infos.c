/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   read_infos.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/15 13:32:47 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/07 13:09:23 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/corewar.h"

/*
** Convertie le Big Endian - Little Endian
*/

int	little_endian(int value)
{
	return ((value & 0x000000FF) << 24 | (value & 0x0000FF00) << 8 |
	(value & 0xFF000000) >> 24 | (value & 0x00FF0000) >> 8);
}

void		read_infos(t_cor *c)
{
	t_header *h;
	int fd;
	int i;

	i = -1;
	while (++i < c->vm->nb_player)
	{
		h = malloc(sizeof(t_header));
		fd = open(c->vm->player[i], O_RDONLY);
		read(fd, h, sizeof(t_header));
		c->chmp[i]->magic = little_endian(h->magic);
		c->chmp[i]->name = ft_strdup(h->prog_name);
		c->chmp[i]->comment = ft_strdup(h->comment);
		if ((c->chmp[i]->champ_size = little_endian(h->prog_size)) > 682)
			ft_exit(3, c->chmp[i]->name);
		c->chmp[i]->infos = ft_strnew(c->chmp[i]->champ_size);
		read(fd, c->chmp[i]->infos, c->chmp[i]->champ_size);
		close(fd);
		free(h);
	}
}
