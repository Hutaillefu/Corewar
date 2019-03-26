/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   error.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/15 13:37:01 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/26 17:33:27 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/corewar.h"

void	del_list(t_list2 *l)
{
	while (l)
	{
		free(l->head);
		l->head = NULL;
		l->head = l->head->next;
	}
}

void    ft_exit(t_logs *logs, int error, char *s, t_cor *c)
{
	int i;

	i = -1;
	// if (error == 0)
	// 	ft_printf(logs, "Usage: ./corewar [-d N -v | -n N] <champion1.cor> <...>\n");
	// if (error == 1)
	// 	ft_printf(logs, "Error parsing ac < 2 or open == -1\n");
	// if (error == 2)
	// 	ft_printf(logs, "Error not files '.cor'\n");
	// if (error == 3)
	// 	ft_printf(logs, "Error: %s has too large a code (> 682 bytes)\n", s);
	// if (error == 5)
	// 	ft_printf(logs, "Error: Flag -d doit etre suivi d'une valeur positive\n");
	// if (error == 6)
	// 	ft_printf(logs, "Too many champions\n");
	// if (error == 7)
	// 	ft_printf(logs, "Can't read source file %s\n", s);
	// if (error == 8)
	// 	ft_putstr("Error malloc\n");
	if (error > 0)
		s = NULL;
	dump_logs(logs);
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
	exit(1);
}
