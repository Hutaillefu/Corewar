/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/10 14:53:51 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/25 20:29:52 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/corewar.h"

void		ft_print_winner(t_cor *c)
{
	int j;

	j = -1;
	while (++j < c->vm->nb_player)
	{
		if (c->chmp[j]->num == c->vm->chmp_win_num)
		{
			ft_printf(&(c->vm->logs), "Contestant %d, \"%s\", has won !\n",
			-c->vm->chmp_win_num, c->chmp[-c->vm->chmp_win_num - 1]->name);
			return ;
		}
	}
}

static void	print_map_color(t_cor *c, int i)
{
	t_node		*tmp;
	short int	draw;

	if (c->vm->map_color)
	{
		draw = 0;
		tmp = c->proc->head;
		while (tmp)
		{
			if (tmp->pc == i)
				draw = 1;
			tmp = tmp->next;
		}
		if (!draw)
			ft_printf(&(c->vm->logs), "%3.2x", c->vm->area[i]);
		else
			ft_printf(&(c->vm->logs), "\033[31;01m%3.2x\033[00m",
			c->vm->area[i]);
	}
	else
		ft_printf(&(c->vm->logs), "%3.2x", c->vm->area[i]);
}

void		print_map(t_cor *c, int octet)
{
	int i;
	int j;

	i = -1;
	j = 0;
	ft_printf(&(c->vm->logs), "0x0000 :");
	while (++i < MEM_SIZE)
	{
		if (i != 0 && j == 0)
			ft_printf(&(c->vm->logs), "%#06x :", i);
		++j;
		print_map_color(c, i);
		if (j == octet)
		{
			j = 0;
			ft_printf(&(c->vm->logs), " \n");
		}
	}
}
