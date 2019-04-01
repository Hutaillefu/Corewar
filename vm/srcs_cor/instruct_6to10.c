/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   instruct_6to10.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/22 20:34:07 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/25 15:22:26 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/corewar.h"

void	i_and(t_node *proc, t_vm *vm)
{
	int p1;
	int p2;

	if ((proc->param[0][1] == REG_CODE &&
	!is_regnum_valid(proc->param[0][0] - 1)) || (proc->param[1][1] == REG_CODE
	&& !is_regnum_valid(proc->param[1][0] - 1)) ||
	(!is_regnum_valid(proc->param[2][0] - 1)) || proc->op.name == NULL)
	{
		adv(vm, proc);
		return ;
	}
	p1 = get_param_value(vm, proc, proc->param[0], 1);
	p2 = get_param_value(vm, proc, proc->param[1], 1);
	proc->reg[proc->param[2][0] - 1] = p1 & p2;
	proc->carry = !proc->reg[proc->param[2][0] - 1];
	if (vm->verbose & V_OP)
		ft_printf(&(vm->logs), "P% 5d | and %d %d r%d\n", proc->num,
		p1, p2, proc->param[2][0]);
	adv(vm, proc);
}

void	i_or(t_node *proc, t_vm *vm)
{
	int p1;
	int p2;

	if ((proc->param[0][1] == REG_CODE &&
	!is_regnum_valid(proc->param[0][0] - 1)) || (proc->param[1][1] ==
	REG_CODE && !is_regnum_valid(proc->param[1][0] - 1)) ||
	(!is_regnum_valid(proc->param[2][0] - 1)) || proc->op.name == NULL)
	{
		adv(vm, proc);
		return ;
	}
	p1 = get_param_value(vm, proc, proc->param[0], 1);
	p2 = get_param_value(vm, proc, proc->param[1], 1);
	proc->reg[proc->param[2][0] - 1] = p1 | p2;
	proc->carry = !proc->reg[proc->param[2][0] - 1];
	if (vm->verbose & V_OP)
		ft_printf(&(vm->logs), "P% 5d | or %d %d r%d\n",
		proc->num, p1, p2, proc->param[2][0]);
	adv(vm, proc);
}

void	i_xor(t_node *proc, t_vm *vm)
{
	int p1;
	int p2;

	if ((proc->param[0][1] == REG_CODE &&
	!is_regnum_valid(proc->param[0][0] - 1)) || (proc->param[1][1] == REG_CODE
	&& !is_regnum_valid(proc->param[1][0] - 1)) ||
	(!is_regnum_valid(proc->param[2][0] - 1)) || proc->op.name == NULL)
	{
		adv(vm, proc);
		return ;
	}
	p1 = get_param_value(vm, proc, proc->param[0], 1);
	p2 = get_param_value(vm, proc, proc->param[1], 1);
	proc->reg[proc->param[2][0] - 1] = p1 ^ p2;
	proc->carry = !proc->reg[proc->param[2][0] - 1];
	if (vm->verbose & V_OP)
		ft_printf(&(vm->logs), "P% 5d | xor %d %d r%d\n",
		proc->num, p1, p2, proc->param[2][0]);
	adv(vm, proc);
}

void	i_zjmp(t_node *proc, t_vm *vm)
{
	int p1;

	p1 = get_param_value(vm, proc, proc->param[0], 1);
	if (proc->carry)
	{
		proc->op_size = (p1);
		if (vm->verbose & V_OP)
			ft_printf(&(vm->logs), "P% 5d | zjmp %d OK\n",
			proc->num, proc->op_size);
		proc->op_size = (p1) % IDX_MOD;
		proc->op_size = proc->op_size < 0 ? MEM_SIZE - (-(proc->op_size))
		: proc->op_size;
	}
	else
	{
		if (vm->verbose & V_OP)
			ft_printf(&(vm->logs), "P% 5d | zjmp %d FAILED\n", proc->num, p1);
		adv(vm, proc);
	}
}

void	i_ldi(t_node *p, t_vm *vm)
{
	int p1;
	int p2;
	int addr;

	if ((p->param[0][1] == REG_CODE && !is_regnum_valid(p->param[0][0] - 1)) ||
	(p->param[1][1] == REG_CODE && !is_regnum_valid(p->param[1][0] - 1)) ||
	(!is_regnum_valid(p->param[2][0] - 1)) || p->op.name == NULL)
	{
		adv(vm, p);
		return ;
	}
	p1 = get_param_value(vm, p, p->param[0], 1);
	p2 = get_param_value(vm, p, p->param[1], 1);
	addr = p->pc + ((p1 + p2) % IDX_MOD);
	p->reg[p->param[2][0] - 1] = read_next_uint(vm, addr, REG_SIZE);
	if (vm->verbose & V_OP)
	{
		ft_printf(&(vm->logs), "P% 5d | ldi %d %d r%d\n", p->num, p1, p2,
		p->param[2][0]);
		ft_printf(&(vm->logs),
		"       | -> load from %d + %d = %d (with pc and mod %d)\n",
		p1, p2, p1 + p2, p->pc + ((p1 + p2) % IDX_MOD));
	}
	adv(vm, p);
}
