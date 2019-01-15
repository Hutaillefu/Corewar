/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/10 14:53:51 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/15 13:24:34 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/corewar.h"

void	print_map(t_cor *c, int octet)
{
	int i;
	int j;

	i = -1;
	j = 0;
	ft_printf("0x0000 :");
	while (++i < MEM_SIZE)
	{
		if (i != 0 && j == 0)
			ft_printf("%#06x :", i);
		++j;
		ft_printf("%3.2x", c->vm->area[i]);
		if (j == octet)
		{
			j = 0;
			ft_printf("\n");
		}
	}
}