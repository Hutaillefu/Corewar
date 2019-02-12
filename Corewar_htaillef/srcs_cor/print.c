/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/10 14:53:51 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/11 17:02:53 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/corewar.h"

void	print_map(t_cor *c, int octet)
{
	int i;
	int j;
	int draw;
	t_node *tmp;

	i = -1;
	j = 0;

	tmp = c->proc->head;
	while (tmp)
	{
		ft_printf("PC is %d\n", tmp->pc);
		tmp = tmp->next;
	}
	printf("%d processus.\n", c->proc->len);
	ft_printf("0x0000 :");
	while (++i < MEM_SIZE)
	{
		if (i != 0 && j == 0)
			ft_printf("%#06x :", i);
		++j;
		draw = 0;
		tmp = c->proc->head;
		while (tmp)
		{
			if (tmp->pc == i)
			{
				ft_printf("\033[32;01m%3.2x\033[00m", c->vm->area[i]);
				draw = 1;
				break;
			}
			tmp = tmp->next;
		}
		if (!draw)
			ft_printf("%3.2x", c->vm->area[i]);
		if (j == octet)
		{
			j = 0;
			ft_printf("\n");
		}
	}
}