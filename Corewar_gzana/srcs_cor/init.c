/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/10 11:21:38 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/15 16:48:52 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/corewar.h"


void	init_map(t_cor *c)
{
	int start;
	int player;

	player = 0;
	start = MEM_SIZE / c->vm->nb_player;
	ft_memcpy(c->vm->area, c->chmp[player]->infos, c->chmp[player]->champ_size);
	while (++player < c->vm->nb_player)
		ft_memsub(c->vm->area, c->chmp[player]->infos, (start * player), c->chmp[player]->champ_size);
}

void	init_chmp(t_cor *c)
{
	int i;

	i = -1;
	while (++i < c->vm->nb_player)
	{
		c->chmp[i] = malloc(sizeof(t_chmp));
		c->chmp[i]->champ_size = 0;
		c->chmp[i]->name = NULL;
		c->chmp[i]->comment = NULL;
		c->chmp[i]->infos = NULL;
		c->chmp[i]->pc = 0;
	}
}

void	init_vm(t_cor *c, char **av, int ac)
{
	c->vm = ft_memalloc(sizeof(t_vm));
	c->vm->carry = 0;
	c->vm->cycle_delta = CYCLE_DELTA;
	c->cycle_to_die = 1536;
	c->vm->nb_live = NBR_LIVE;
	c->vm->nb_player = 0;
	if (!(c->vm->area = malloc(sizeof(unsigned char) * (MEM_SIZE))))
		ft_exit(1);
	ft_memset(c->vm->area, 0, MEM_SIZE);
	c->vm->area[MEM_SIZE + 1] = '\0';
	c->vm->max_chk = MAX_CHECKS;
	c->vm->champ_msize = CHAMP_MAX_SIZE;
	c->vm->cycle = 0;
	c->vm->dump = -1;
	if (check_parse(c, av, ac) == 1)
		ft_exit(1);
	init_chmp(c);
}