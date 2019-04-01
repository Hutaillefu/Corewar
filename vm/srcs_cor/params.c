/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   params.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/22 19:27:37 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/27 16:10:13 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/corewar.h"

/*
** Setup op params for the given chmp.
*/

static int	reg_code(t_node *proc, int param_index, t_vm *vm)
{
	int res;

	res = read_next_uint(vm, proc->pc, 1);
	proc->param[param_index][0] = res;
	proc->param[param_index][1] = REG_CODE;
	proc->pc = (proc->pc + 1) % MEM_SIZE;
	return (1);
}

static int	ind_code(t_node *proc, int param_index, t_vm *vm)
{
	int res;

	res = (short)read_next_uint(vm, proc->pc, 2);
	proc->param[param_index][0] = res;
	proc->param[param_index][1] = IND_CODE;
	proc->pc = (proc->pc + 2) % MEM_SIZE;
	return (1);
}

static int	extract_param(t_vm *vm, t_node *proc, int param_index,
int coding_byte)
{
	int	mask;
	int res;

	if (!vm || !proc)
		return (0);
	mask = proc->op.param_mask[param_index];
	if (coding_byte != -1 ? read_coding_byte(coding_byte,
		param_index + 1) == REG_CODE : 1 && (T_REG & mask))
		return (reg_code(proc, param_index, vm));
	else if (coding_byte != -1 ? read_coding_byte(coding_byte,
		param_index + 1) == DIR_CODE : 1 && (T_DIR & mask) == T_DIR)
	{
		if (proc->op.dir_size == 0)
			res = read_next_uint(vm, proc->pc, 4);
		else
			res = (short)read_next_uint(vm, proc->pc, 2);
		proc->param[param_index][0] = res;
		proc->param[param_index][1] = DIR_CODE;
		proc->pc = (proc->pc + (proc->op.dir_size == 0 ? 4 : 2)) % MEM_SIZE;
		return (1);
	}
	else if (coding_byte != -1 ? read_coding_byte(coding_byte,
	param_index + 1) == IND_CODE : 1 && (T_IND & mask) == T_IND)
		return (ind_code(proc, param_index, vm));
	return (0);
}

/*
** Initializes param to default value.
*/

void		init_param(t_node *proc)
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
