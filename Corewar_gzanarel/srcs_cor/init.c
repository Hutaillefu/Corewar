/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/10 11:21:38 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/25 15:29:56 by gzanarel    ###    #+. /#+    ###.fr     */
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
	ft_printf(&(c->vm->logs), "Introducing contestants...\n");
	while (++player < c->vm->nb_player)
	{
		ft_printf(&(c->vm->logs),
		"* Player %d, weighing %u bytes, \"%s\" (\"%s\") !\n",
		(player + 1), c->chmp[player]->champ_size, c->chmp[player]->name,
		c->chmp[player]->comment);
		ft_memsub(c->vm->area, c->chmp[player]->infos, (start * player),
		c->chmp[player]->champ_size);
	}
}

static void	init_num_chmp(t_cor *c, int i)
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
		c->chmp[i]->num = (i + 1) * -1;
}

void	init_proc(t_cor *c, t_list2 *proc)
{
	int i;

	i = -1;
	ft_memset(proc, 0, sizeof(t_list2));
	while (++i < c->vm->nb_player)
	{
		if (!(c->chmp[i] = (t_chmp *)ft_memalloc(sizeof(t_chmp))))
			ft_exit(&(c->vm->logs), 8, NULL, c);
		c->chmp[i]->champ_size = 0;
		c->chmp[i]->name = NULL;
		c->chmp[i]->comment = NULL;
		c->chmp[i]->infos = NULL;
		init_num_chmp(c, i);
		add_element_end(&(proc), c, c->chmp[i], i);
	}
	proc->nb = c->vm->nb_player;
	c->vm->chmp_win_num = -c->proc->head->num;
}

void	init_vm(t_cor *c, t_vm *vm)
{
	int j;

	j = -1;
	ft_memset(vm, 0, sizeof(t_vm));
	vm->cycle_delta = CYCLE_DELTA;
	vm->cycle_to_die = CYCLE_TO_DIE;
	if (!(vm->area = malloc(sizeof(unsigned char) * (MEM_SIZE + 1))))
		ft_exit(&(vm->logs), 8, NULL, c);
	ft_memset(vm->area, 0, MEM_SIZE);
	vm->area[MEM_SIZE] = '\0';
	vm->champ_msize = CHAMP_MAX_SIZE;
	vm->dump = -1;
	vm->max_chk = 1;
	init_logs(&(vm->logs));
	while (++j < MAX_PLAYERS)
		vm->num[j] = -1;
}

t_cor	*init_cor(char **av, int ac)
{
	t_cor *c;

	if (!(c = ft_memalloc(sizeof(t_cor))))
		ft_exit(NULL, 8, NULL, c);
	if (!(c->vm = ft_memalloc(sizeof(t_vm))))
		ft_exit(NULL, 8, NULL, c);
	if (!(c->proc = ft_memalloc(sizeof(t_list2))))
		ft_exit(NULL, 8, NULL, c);
	init_vm(c, c->vm);
	if (check_parse(c, c->vm, av, ac) == 1)
		ft_exit(&(c->vm->logs), 1, NULL, c);
	init_proc(c, c->proc);
	return (c);
}
