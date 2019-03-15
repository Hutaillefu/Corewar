/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/10 14:53:51 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/13 15:49:17 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/corewar.h"

void		ft_print_winner(t_cor *c)
{
	int j;
	int last;
	int win;

	win = 0;
	j = -1;
	last = 0;
	while (++j < c->vm->nb_player)
	{
		if (c->chmp[j]->last_live >= last)
		{
			last = c->chmp[j]->last_live;
			win = j;
		}
	}
	ft_printf(&(c->vm->logs), "Contestant %d, \"%s\", has won !\n", win + 1, c->chmp[win]->name);
}


void	print_map(t_cor *c, int octet)
{
	int i;
	int j;
	int draw;
	t_node *tmp;

	i = -1;
	j = 0;

	// ft_printf("nb_proc: %d\n", c->proc->len);
	// tmp = c->proc->head;
	// while (tmp)
	// {
	// 	ft_printf("proc: %d\n", tmp->num);
	// 	tmp = tmp->next;
	// }
	// printf("NB Procs: %d\n", c->proc->len);
	tmp = c->proc->head;
	ft_printf(&(c->vm->logs), "0x0000 :");
	while (++i < MEM_SIZE)
	{
		if (i != 0 && j == 0)
			ft_printf(&(c->vm->logs), "%#06x :", i);
		++j;
		draw = 0;
		tmp = c->proc->head;
		// while (tmp)
		// {
		// 	if (tmp->pc == i)
		// 	{
		// 		ft_printf(&(c->vm->logs), "\033[31;01m%3.2x\033[00m", c->vm->area[i]);
		// 		draw = 1;
		// 		break;
		// 	}
		// 	tmp = tmp->next;
		// }
		if (!draw)
			ft_printf(&(c->vm->logs), "%3.2x", c->vm->area[i]);
		if (j == octet)
		{
			j = 0;
			ft_printf(&(c->vm->logs), " \n");
		}
	}
}