/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/09 15:04:49 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/26 17:34:32 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/corewar.h"

int		main(int ac, char **av)
{
	t_cor *c;
	int i = -1;

	c = init_cor(av, ac);
	read_infos(c);
	init_map(c);
	cycle(c);
	ft_print_winner(c);
	dump_logs(&(c->vm->logs));
	if (c->proc)
		del_list(c->proc);
	while (++i < c->vm->nb_player)
	{
		!c->chmp[i]->name ? free(c->chmp[i]->name) : 0;
		!c->chmp[i]->comment ? free(c->chmp[i]->comment) : 0;
		!c->chmp[i]->infos ? free(c->chmp[i]->infos) : 0;
		!c->chmp[i] ? free(c->chmp[i]) : 0;
	}
	if (c->vm)
	{
		if (c->vm->area)
			free(c->vm->area);
		free(c->vm);
	}
	if (c)
		free(c);
	return (0);
}
