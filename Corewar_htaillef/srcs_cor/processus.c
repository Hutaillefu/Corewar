/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   processus.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/16 13:45:58 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/17 18:13:41 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/corewar.h"

int	start_processus(t_cor *cor, t_node *proc)
{
	if (proc->op.opcode == 0)
		i_lfork(proc, cor);
	else if (proc->op.opcode == 1)
		i_live(proc, cor);
	else if (proc->op.opcode == 2)
		i_ld(proc, cor->vm);
	else if (proc->op.opcode == 3)
		i_st(proc, cor->vm);
	else if (proc->op.opcode == 4)
		i_add(proc, cor->vm);
	else if (proc->op.opcode == 5)
		i_sub(proc, cor->vm);
	else if (proc->op.opcode == 6)
		i_and(proc, cor->vm);	
	else if (proc->op.opcode == 7)
		i_or(proc, cor->vm);	
	else if (proc->op.opcode == 8)
		i_xor(proc, cor->vm);
	else if (proc->op.opcode == 9)
		i_zjmp(proc, cor->vm);
	else if (proc->op.opcode == 10)
		i_ldi(proc, cor->vm);
	if (proc->op.opcode == 11)
		i_sti(proc, cor->vm);
	if (proc->op.opcode == 12)
	{
		i_fork(proc, cor);
		proc->pc = (proc->pc + proc->op_size) % MEM_SIZE;
		proc->exec = 0;
		return (1);
	}
	else if (proc->op.opcode == 13)
		i_lld(proc, cor->vm);
	else if (proc->op.opcode == 14)
		i_lldi(proc, cor->vm);	
	proc->pc = (proc->pc + proc->op_size) % MEM_SIZE;
	// printf("PC %d\n", proc->pc);
	proc->exec = 0;
	return (0);
}

void	load_processus(int start, t_node *proc)
{
	proc->exec = start + proc->op.nb_cycles;
}