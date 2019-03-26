/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/09 15:04:49 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/26 18:37:47 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/corewar.h"

int		main(int ac, char **av)
{
	t_cor *c;

	if (ac > 1)
	{
		c = init_cor(av, ac);
		read_infos(c);
		init_map(c);
		cycle(c);
		ft_print_winner(c);
		dump_logs(&(c->vm->logs));
		free_cor(&c);
	}
	else
		print_usage();
	return (0);
}
