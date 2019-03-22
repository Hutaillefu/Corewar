/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   instruct_11to15.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/22 20:35:42 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/22 20:58:45 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/corewar.h"

void	i_sti(t_node *proc, t_vm *vm)
{
	int addr;
	int	p1;
	int p2;
	int	p3;

	if ((!is_regnum_valid(proc->param[0][0] - 1) || !proc->op.name) ||
	(proc->param[1][1] == REG_CODE && !is_regnum_valid(proc->param[1][0] - 1)) ||
	(proc->param[2][1] == REG_CODE && !is_regnum_valid(proc->param[2][0] - 1)) || proc->op.name == NULL)
	{
		if (vm->verbose & V_ADV)
			adv(vm, proc->pc, proc->op_size);
		return ;
	}
	addr = 0;
	p1 = get_param_value(vm, proc, proc->param[1], 1);
	p2 = get_param_value(vm, proc, proc->param[2], 1);
	p3 = get_param_value(vm, proc, proc->param[0], 1);
	addr = proc->pc + ((p1 + p2) % IDX_MOD);
	write_uint(vm, p3, addr, REG_SIZE);
	if (vm->verbose & V_OP)
	{
		// addr %= MEM_SIZE;
		ft_printf(&(vm->logs), "P% 5d | sti r%d %d %d\n", proc->num, proc->param[0][0], p1, p2);
		ft_printf(&(vm->logs), "       | -> store to %d + %d = %d (with pc and mod %d)\n", p1, p2, p1 + p2, addr);
	}
	if (vm->verbose & V_ADV)
		adv(vm, proc->pc, proc->op_size);
}

void	i_fork(t_node *proc, t_cor *cor)
{
	int p1;
	t_node *child;

	p1 = get_param_value(cor->vm, proc, proc->param[0], 1);
	if (!(child = clone_proc(proc)))
		return ;
	child->pc = (proc->pc + (p1 % IDX_MOD)) % MEM_SIZE;
	child->pc_b = child->pc;
	push_front(&(cor->proc), child);
	child->num = cor->proc->nb;
	if (cor->vm->verbose & V_OP)
		ft_printf(&(cor->vm->logs), "P% 5d | fork %d (%d)\n", proc->num, p1, child->pc);
	if (cor->vm->verbose & V_ADV)
		adv(cor->vm, proc->pc, proc->op_size);
}

void	i_lld(t_node *proc, t_vm *vm)
{
	int p1;

	if (!is_regnum_valid(proc->param[1][0] - 1) || proc->op.name == NULL)
	{
		if (vm->verbose & V_ADV)	
			adv(vm, proc->pc, proc->op_size);
		return ;
	}
	p1 = get_param_value(vm, proc, proc->param[0], 0);
	proc->reg[proc->param[1][0] - 1] = p1;
	proc->carry = !proc->reg[proc->param[1][0] - 1];
	if (vm->verbose & V_OP)
		ft_printf(&(vm->logs), "P% 5d | lld %d r%d\n", proc->num, p1, proc->param[1][0]);
	if (vm->verbose & V_ADV)
		adv(vm, proc->pc, proc->op_size);
}

void	i_lldi(t_node *proc, t_vm *vm)
{
	int p1;
	int p2;
	int addr;

	if ((proc->param[0][1] == REG_CODE && !is_regnum_valid(proc->param[0][0] - 1)) ||
	(proc->param[1][1] == REG_CODE && !is_regnum_valid(proc->param[1][0] - 1)) ||
	(!is_regnum_valid(proc->param[2][0] - 1)) || proc->op.name == NULL)
	{
		if (vm->verbose & V_ADV)
			adv(vm, proc->pc, proc->op_size);
		return ;
	}
	p1 = get_param_value(vm, proc, proc->param[0], 0);
	p2 = get_param_value(vm, proc, proc->param[1], 0);
	addr = proc->pc + (p1 + p2) % MEM_SIZE;
	// addr = addr < 0 ? MEM_SIZE -(-addr) : addr;
	//addr %= MEM_SIZE;
	proc->reg[proc->param[2][0] - 1] = read_next_uint(vm, addr, REG_SIZE);
	proc->carry = !proc->reg[proc->param[2][0] - 1];
	if (vm->verbose & V_OP)
	{
		ft_printf(&(vm->logs), "P% 5d | lldi %d %d r%d\n", proc->num, p1, p2, proc->param[2][0]);
		ft_printf(&(vm->logs), "       | -> load from %d + %d = %d (with pc and mod %d)\n", p1, p2, p1 + p2, p1 + p2);
	}
	if (vm->verbose & V_ADV)
		adv(vm, proc->pc, proc->op_size);
}

void	i_lfork(t_node *proc, t_cor *cor)
{
	int p1;
	t_node *child;

	p1 = get_param_value(cor->vm, proc, proc->param[0], 1);
	if (!(child = clone_proc(proc)))
		return ;
	child->pc = (proc->pc + p1) % MEM_SIZE;
	child->pc = child->pc < 0 ? MEM_SIZE -(-child->pc) : child->pc;
	child->pc_b = child->pc;
	push_front(&(cor->proc), child);
	child->num = cor->proc->nb;
	if (cor->vm->verbose & V_OP)
		ft_printf(&(cor->vm->logs), "P% 5d | lfork %d (%d)\n", proc->num, p1, proc->pc + p1);
	if (cor->vm->verbose & V_ADV)
		adv(cor->vm, proc->pc, proc->op_size);
}
