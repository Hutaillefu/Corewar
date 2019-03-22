/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_instruct.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: htaillef <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/22 15:27:24 by htaillef     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/22 15:27:26 by htaillef    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

/*
  ** Return the matching op.
*/

t_op		get_op_by_opcode(int opcode)
{
	int i;

	i = 0;
	while (op_tab[i].name)
	{
		if (op_tab[i].opcode == opcode)
			return (op_tab[i]);
		i++;
	}
	return (op_tab[i]);
}

static int	load_codingbyte(t_node *proc, t_vm *vm, int coding_byte,
int pc_base)
{
	if (proc->op.coding_byte)
		coding_byte = (int)vm->area[++(proc->pc) % MEM_SIZE];
	if (proc->op.coding_byte && !is_codingbyte_valid(proc, coding_byte))
	{
		proc->pc = pc_base;
		proc->op_size = get_codingbyte_len(proc, coding_byte) + 1 + 1;
		return (0);
	}
	return (1);
}

int			load(t_vm *vm, t_node *proc)
{
	t_op	op;
	int		coding_byte;
	int		pc_base;

	pc_base = proc->pc;
	proc->op.coding_byte = -1;
	proc->op.nb_cycles = 1;
	proc->op.opcode = -1;
	proc->op.name = NULL;
	proc->op.nb_params = 0;
	if (!(op = get_op_by_opcode((int)vm->area[proc->pc])).name)
	{
		proc->op.opcode = -1;
		proc->op_size = 1;
		return (0);
	}
	proc->op = op;
	coding_byte = -1;
	if (!load_codingbyte(proc, vm, coding_byte, pc_base))
		return (0);
	proc->pc = (proc->pc + 1) % MEM_SIZE;
	proc->op_size = proc->pc - pc_base;
	proc->pc = pc_base;
	return (1);
}

int			exec(t_vm *vm, t_node *proc)
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
			return (0);
		}
	}
	proc->pc = (proc->pc + 1) % MEM_SIZE;
	extract_params(vm, proc, coding_byte);
	proc->op_size = proc->pc < pc_base ? (MEM_SIZE - pc_base + proc->pc)
	: proc->pc - pc_base;
	proc->pc = pc_base;
	return (1);
}
