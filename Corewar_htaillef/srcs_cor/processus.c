/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   processus.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/16 13:45:58 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/17 15:33:06 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/corewar.h"

void	start_processus(t_cor *cor, t_chmp *chmp)
{
	//printf("chmp->name %s\n", chmp->name);
	if (chmp->op.opcode == 1)
		i_live(chmp, cor);
	if (chmp->op.opcode == 11)
		i_sti(chmp, cor->vm);
	else if (chmp->op.opcode == 4)
		i_add(chmp, cor->vm);
	else if (chmp->op.opcode == 5)
		i_sub(chmp, cor->vm);
	else if (chmp->op.opcode == 6)
		i_and(chmp, cor->vm);	
	else if (chmp->op.opcode == 7)
		i_or(chmp, cor->vm);	
	else if (chmp->op.opcode == 8)
		i_xor(chmp, cor->vm);	
	//printf("pc: %d\n", chmp->pc);
	chmp->pc += chmp->op_size;
	//printf("pc: %d\n", chmp->pc);
	chmp->exec = 0;
}

void	load_processus(int start, t_chmp *chmp)
{
	chmp->exec = start + chmp->op.nb_cycles;
}