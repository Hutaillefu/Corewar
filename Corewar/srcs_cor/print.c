/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/10 14:53:51 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/10 17:37:18 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/corewar.h"

void	print_map(t_cor *c)
{
	printf("Start Map\n");
	int i;
	int j;

	i = -1;
	j = 0;
	while (++i < MEM_SIZE)
	{
		++j;
		printf("%3.2x", c->vm->area[i]);
		if (j == 32)
		{
			j = 0;
			printf("\n");
		}
	}
	printf("\nEnd Map\n");
}