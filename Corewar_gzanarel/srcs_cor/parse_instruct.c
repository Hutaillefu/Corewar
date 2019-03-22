/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_instruct.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/22 19:15:51 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/22 19:57:02 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/corewar.h"

static void	re_init_op(t_node *proc)
{
	proc->op.coding_byte = -1;
	proc->op.nb_cycles = 1;
	proc->op.opcode = -1;
	proc->op.name = NULL;
	proc->op.nb_params = 0;
}

void		load(t_vm *vm, t_node *proc)
{
	t_op	op;
	int		coding_byte;
	int		pc_base;

	pc_base = proc->pc;
	re_init_op(proc);
	if (!(op = get_op_by_opcode((int)vm->area[proc->pc])).name)
	{
		proc->op.opcode = -1;
		proc->op_size = 1;
		return ;
	}
	proc->op = op;
	coding_byte = -1;
	if (op.coding_byte)
		coding_byte = (int)vm->area[++(proc->pc) % MEM_SIZE];
	if (op.coding_byte && !is_codingbyte_valid(proc, coding_byte))
	{
		proc->pc = pc_base;
		proc->op_size = get_codingbyte_len(proc, coding_byte) + 1 + 1;
		return ;
	}
	proc->pc = (proc->pc + 1) % MEM_SIZE;
	proc->op_size = proc->pc - pc_base;
	proc->pc = pc_base;
}

void		exec(t_vm *vm, t_node *proc)
{
	int		coding_byte;
	int		pc_base;

	pc_base = proc->pc;
	coding_byte = -1;
	if (proc->op.coding_byte > 0)
	{
		coding_byte = (int)vm->area[++(proc->pc) % MEM_SIZE];
		if (!is_codingbyte_valid(proc, coding_byte))
		{
			proc->op.name = NULL;
			proc->pc = pc_base;
			proc->op_size = get_codingbyte_len(proc, coding_byte) + 1 + 1;
			return ;
		}
	}
	proc->pc = (proc->pc + 1) % MEM_SIZE;
	extract_params(vm, proc, coding_byte);
	proc->op_size = proc->pc < pc_base ?
	(MEM_SIZE - pc_base + proc->pc) : proc->pc - pc_base;
	proc->pc = pc_base;
}
