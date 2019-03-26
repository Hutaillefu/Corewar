/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/09 15:04:49 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/26 13:25:28 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/corewar.h"

int		main(int ac, char **av)
{
	t_cor *c;

	c = init_cor(av, ac);
	read_infos(c);
	init_map(c);
	cycle(c);
	ft_print_winner(c);
	dump_logs(&(c->vm->logs));
	if (!c->proc)
		del_list(c->proc);
	if (!c->vm)
		free(c->vm);
	if (!c)
		free(c);
	return (0);
}
