/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   instruct_1to5.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/22 20:31:51 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/22 20:48:36 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/corewar.h"

void	i_live(t_node *proc, t_cor *cor)
{
	int		champ_num;
	t_chmp	*chmp;

	champ_num = read_next_uint(cor->vm, proc->pc + 1, 4);
	cor->vm->nb_live++;
	proc->last_live = cor->vm->cycle;
	if (cor->vm->verbose & V_OP)
		ft_printf(&(cor->vm->logs), "P% 5d | live %d\n", proc->num, champ_num);
	if ((chmp = get_chmp_by_num(cor, champ_num)) && (cor->vm->verbose & V_LIVE))
		ft_printf(&(cor->vm->logs), "Player %d (%s) is said to be alive\n",
		-chmp->num, chmp->name);
	if (cor->vm->verbose & V_ADV)
		adv(cor->vm, proc->pc, proc->op_size);
	if (!chmp)
		return ;
	cor->vm->chmp_win_num = champ_num;
}

void	i_ld(t_node *proc, t_vm *vm)
{
	int p1;

	p1 = get_param_value(vm, proc, proc->param[0], 1);
	if (!is_regnum_valid(proc->param[1][0] - 1) || proc->op.name == NULL)
	{
		if (vm->verbose & V_ADV)
			adv(vm, proc->pc, proc->op_size);
		return ;
	}
	proc->reg[proc->param[1][0] - 1] = p1;
	proc->carry = !proc->reg[proc->param[1][0] - 1];
	if (vm->verbose & V_OP)
		ft_printf(&(vm->logs), "P% 5d | ld %d r%d\n", proc->num, p1,
		proc->param[1][0]);
	if (vm->verbose & V_ADV)
		adv(vm, proc->pc, proc->op_size);
}

void	i_st(t_node *proc, t_vm *vm)
{
	int p1;
	int	p2;
	int addr;

	if (!is_regnum_valid(proc->param[0][0] - 1) || !proc->op.name)
	{
		if (vm->verbose & V_ADV)
			adv(vm, proc->pc, proc->op_size);
		return ;
	}
	p1 = get_param_value(vm, proc, proc->param[0], 1);
	p2 = proc->param[1][0];
	if (proc->param[1][1] == IND_CODE)
	{
		addr = proc->pc + (p2 % IDX_MOD);
		addr = addr < 0 ? MEM_SIZE - (-addr) : addr;
		write_uint(vm, p1, addr, REG_SIZE);
	}
	else if (proc->param[1][1] == REG_CODE)
	{
		if (!is_regnum_valid(p2 - 1))
		{
			if (vm->verbose & V_ADV)
				adv(vm, proc->pc, proc->op_size);
			return ;
		}
		proc->reg[p2 - 1] = p1;
	}
	if (vm->verbose & V_OP)
		ft_printf(&(vm->logs), "P% 5d | st r%d %d\n", proc->num,
		proc->param[0][0], p2);
	if (vm->verbose & V_ADV)
		adv(vm, proc->pc, proc->op_size);
}

void	i_add(t_node *proc, t_vm *vm)
{
	int p1;
	int p2;

	if (!is_regnum_valid(proc->param[0][0] - 1) ||
		!is_regnum_valid(proc->param[1][0] - 1) ||
		!is_regnum_valid(proc->param[2][0] - 1) || proc->op.name == NULL)
	{
		if (vm->verbose & V_ADV)
			adv(vm, proc->pc, proc->op_size);
		return ;
	}
	p1 = get_param_value(vm, proc, proc->param[0], 1);
	p2 = get_param_value(vm, proc, proc->param[1], 1);
	proc->reg[proc->param[2][0] - 1] = p1 + p2;
	proc->carry = !proc->reg[proc->param[2][0] - 1];
	if (vm->verbose & V_OP)
		ft_printf(&(vm->logs), "P% 5d | add r%d r%d r%d\n", proc->num,
		proc->param[0][0], proc->param[1][0], proc->param[2][0]);
	if (vm->verbose & V_ADV)
		adv(vm, proc->pc, proc->op_size);
}

void	i_sub(t_node *proc, t_vm *vm)
{
	int p1;
	int p2;

	if (!is_regnum_valid(proc->param[0][0] - 1) ||
	!is_regnum_valid(proc->param[1][0] - 1)
	|| !is_regnum_valid(proc->param[2][0] - 1) || proc->op.name == NULL)
	{
		if (vm->verbose & V_ADV)
			adv(vm, proc->pc, proc->op_size);
		return ;
	}
	p1 = get_param_value(vm, proc, proc->param[0], 1);
	p2 = get_param_value(vm, proc, proc->param[1], 1);
	proc->reg[proc->param[2][0] - 1] = p1 - p2;
	proc->carry = !proc->reg[proc->param[2][0] - 1];
	if (vm->verbose & V_OP)
		ft_printf(&(vm->logs), "P% 5d | sub r%d r%d r%d\n", proc->num,
		proc->param[0][0], proc->param[1][0], proc->param[2][0]);
	if (vm->verbose & V_ADV)
		adv(vm, proc->pc, proc->op_size);
}
