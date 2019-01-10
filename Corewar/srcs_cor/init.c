/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/10 11:21:38 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/10 17:21:10 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/corewar.h"

void	init_vm(t_cor *c)
{
	c->vm = ft_memalloc(sizeof(t_vm));
	c->vm->carry = 0;
	c->vm->cycle_delta = CYCLE_DELTA;
	c->cycle_to_die = 1536;
	c->vm->nb_live = NBR_LIVE;
	c->vm->nb_player = 0;
	if (!(c->vm->area = malloc(sizeof(unsigned char) * (MEM_SIZE))))
		ft_exit();
	ft_memset(c->vm->area, 0, MEM_SIZE);
	c->vm->area[MEM_SIZE + 1] = '\0';
	c->vm->pc = 0;
	c->vm->max_chk = MAX_CHECKS;
	c->vm->champ_msize = CHAMP_MAX_SIZE;
	c->vm->cycle = 0;
}