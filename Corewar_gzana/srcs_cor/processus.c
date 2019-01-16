/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   processus.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/16 13:45:58 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/16 14:44:22 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/corewar.h"

void	start_processus(t_chmp *chmp, t_vm *vm)
{
	if (chmp->op.opcode == 11)
		i_sti(chmp, vm);
	chmp->pc = chmp->op_size;
	chmp->exec = 0;
}

void	load_processus(int start, t_cor *c, t_chmp *chmp)
{
	chmp->exec = start + chmp->op.nb_cycles;
}