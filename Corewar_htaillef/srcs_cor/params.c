/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   params.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: htaillef <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/22 15:49:10 by htaillef     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/22 15:49:11 by htaillef    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

/*
  ** Initializes param to default value.
*/

static void		init_param(t_node *proc)
{
	if (!proc)
		return ;
	proc->op_size = 0;
	proc->param[0][0] = -1;
	proc->param[0][1] = -1;
	proc->param[1][0] = -1;
	proc->param[1][1] = -1;
	proc->param[2][0] = -1;
	proc->param[2][1] = -1;
}

static int	extract_dir(t_node *proc, t_vm *vm, int param_index)
{
	proc->param[param_index][0] = proc->op.dir_size == 0 ?
	read_next_uint(vm, proc->pc, 4) :
	(short)read_next_uint(vm, proc->pc, 2);
	proc->param[param_index][1] = DIR_CODE;
	proc->pc = (proc->pc + (proc->op.dir_size == 0 ? 4 : 2)) % MEM_SIZE;
	return (1);
}

/*
  ** Setup op params for the given chmp.
*/

static int	extract_param(t_vm *vm, t_node *p, int param_index, int codingbyte)
{
	int	mask;

	if (!vm || !p)
		return (0);
	mask = p->op.param_mask[param_index];
	if (codingbyte != -1 ? read_coding_byte(codingbyte, param_index + 1)
	== REG_CODE : 1 && (T_REG & mask))
	{
		p->param[param_index][0] = read_next_uint(vm, p->pc, 1);
		p->param[param_index][1] = REG_CODE;
		p->pc = (p->pc + 1) % MEM_SIZE;
		return (1);
	}
	else if (codingbyte != -1 ? read_coding_byte(codingbyte, param_index + 1)
	== DIR_CODE : 1 && (T_DIR & mask) == T_DIR)
		return (extract_dir(p, vm, param_index));
	else if (codingbyte != -1 ? read_coding_byte(codingbyte, param_index + 1)
	== IND_CODE : 1 && (T_IND & mask) == T_IND)
	{
		p->param[param_index][0] = (short)read_next_uint(vm, p->pc, 2);
		p->param[param_index][1] = IND_CODE;
		p->pc = (p->pc + 2) % MEM_SIZE;
		return (1);
	}
	return (0);
}

/*
  ** Return the value of param according to his type.
*/

int			get_param_value(t_vm *vm, t_node *proc, int param[2], int mod)
{
	int addr;

	if (param[1] == DIR_CODE)
		return (param[0]);
	else if (param[1] == REG_CODE)
		return (proc->reg[param[0] - 1]);
	else if (param[1] == IND_CODE)
	{
		if (mod)
			addr = (proc->pc + (param[0] % IDX_MOD));
		else
			addr = (proc->pc + param[0]) % MEM_SIZE;
		addr = addr < 0 ? (MEM_SIZE - (-addr)) % MEM_SIZE : addr % MEM_SIZE;
		return (read_next_uint(vm, addr, 4));
	}
	return (-1);
}

int			extract_params(t_vm *vm, t_node *proc, int coding_byte)
{
	if (!vm || !(vm->area) || !(proc))
		return (0);
	init_param(proc);
	if (proc->op.nb_params >= 1 && !extract_param(vm, proc, 0, coding_byte))
		return (0);
	if (proc->op.nb_params >= 2 && !extract_param(vm, proc, 1, coding_byte))
		return (0);
	if (proc->op.nb_params == 3 && !extract_param(vm, proc, 2, coding_byte))
		return (0);
	return (1);
}
