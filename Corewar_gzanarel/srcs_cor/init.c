/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/10 11:21:38 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/17 17:38:47 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/corewar.h"


void	init_map(t_cor *c)
{
	int start;
	int player;

	player = -1;
	start = MEM_SIZE / c->vm->nb_player;
	while (++player < c->vm->nb_player)
	{
		ft_printf("* Player %d (nb: %X(%d)), weighing %u bytes, \"%s\" (%s) !\n", (player + 1), c->chmp[player]->num, c->chmp[player]->num, c->chmp[player]->champ_size, c->chmp[player]->name, c->chmp[player]->comment);
		ft_memsub(c->vm->area, c->chmp[player]->infos, (start * player), c->chmp[player]->champ_size);
	}
}

void	init_num_chmp(t_cor *c, int i)
{
	int j;

	j = -1;
	if (c->vm->num[i] >= 0)
	{
		while (++j < i)
			if (c->chmp[j]->num == -c->vm->num[i])
			{
				c->vm->num[i] += 1;
				j = -1;
			}
		c->chmp[i]->num = c->vm->num[i] * -1;
	}
	else
	{
		c->chmp[i]->num = (i + 1) * -1;
	}
}

void	init_chmp(t_cor *c)
{
	int i;

	i = -1;
	c->proc = (t_list2 *)malloc(sizeof(t_list2)); // a securiser
	c->proc->head = NULL;
	c->proc->tail = NULL;
	c->proc->len = 0;
	while (++i < c->vm->nb_player)
	{
		c->chmp[i] = (t_chmp *)malloc(sizeof(t_chmp));
		c->chmp[i]->champ_size = 0;
		c->chmp[i]->name = NULL;
		c->chmp[i]->comment = NULL;
		c->chmp[i]->infos = NULL;
		init_num_chmp(c, i);
		add_element_end(&(c->proc), c, c->chmp[i], i);
	}
}

void	init_vm(t_cor *c, char **av, int ac)
{
	int j;

	j = -1;
	c->vm = ft_memalloc(sizeof(t_vm));
	c->vm->cycle_delta = CYCLE_DELTA;
	c->vm->cycle_to_die = CYCLE_TO_DIE;
	c->vm->nb_live = 0;
	c->vm->nb_player = 0;
	c->vm->chmp_win_num = 0;
	if (!(c->vm->area = malloc(sizeof(unsigned char) * (MEM_SIZE))))
		ft_exit(1);
	ft_memset(c->vm->area, 0, MEM_SIZE);
	c->vm->area[MEM_SIZE + 1] = '\0';
	c->vm->max_chk = MAX_CHECKS;
	c->vm->champ_msize = CHAMP_MAX_SIZE;
	c->vm->cycle = 0;
	c->vm->dump = -1;
	while (++j < MAX_PLAYERS)
		c->vm->num[j] = -1;
	if (check_parse(c, av, ac) == 1)
		ft_exit(1);
	init_chmp(c);
}