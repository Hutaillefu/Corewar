/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/10 14:53:51 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/25 16:11:41 by gzanarel    ###    #+. /#+    ###.fr     */
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
	printf("nb_live: %d\n", c->vm->nb_live);
	// while (tmp)
	// {
	// 	ft_printf("PC is %d | last_live PC: %d\n", tmp->pc, tmp->last_live);
	// 	tmp = tmp->next;
	// }
	ft_printf("cycle: %d\n", c->vm->cycle);
	ft_printf("last live chmp: %d\n", c->chmp[0]->last_live);
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
				ft_printf("\033[31;01m%3.2x\033[00m", c->vm->area[i]);
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