/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   processus.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/16 13:45:58 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/16 16:53:36 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/corewar.h"

void	start_processus(t_chmp *chmp, t_vm *vm)
{
	//printf("chmp->name %s\n", chmp->name);
	if (chmp->op.opcode == 11)
		i_sti(chmp, vm);
	else if (chmp->op.opcode == 4)
		i_add(chmp, vm);
	else if (chmp->op.opcode == 5)
		i_sub(chmp, vm);
	else if (chmp->op.opcode == 6)
		i_and(chmp, vm);	
	else if (chmp->op.opcode == 7)
		i_or(chmp, vm);	
	else if (chmp->op.opcode == 8)
		i_xor(chmp, vm);	
	//printf("pc: %d\n", chmp->pc);
	chmp->pc += chmp->op_size;
	//printf("pc: %d\n", chmp->pc);
	chmp->exec = 0;
}

void	load_processus(int start, t_cor *c, t_chmp *chmp)
{
	printf("load\n");
	chmp->exec = start + chmp->op.nb_cycles;
}