/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   instructions.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/11 13:33:40 by htaillef     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/07 15:46:45 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

int		is_regnum_valid(int regnum)
{
	return (regnum >=0 && regnum <= 15);
}

void	adv(t_vm *vm, int pc, int opsize)
{
	int i;

	i = -1;
	if (pc == 0)
		ft_printf("ADV %d (0x0000 -> %#06x)", opsize, pc + opsize);
	else
		ft_printf("ADV %d (%#06x -> %#06x)", opsize, pc, pc + opsize);
	while (++i < opsize)
	{
		ft_printf("%3.2x", vm->area[pc + i]);
	}
	ft_printf(" \n");
}

/*
  ** Write in the memory at start_index value coded on bytes_len.
*/
void	write_uint(t_vm *vm, int value, int start_index, int bytes_len)
{
	int	i;
	int dec;
	if (!vm)
		return ;
	i = 0;
	dec = (bytes_len - 1) * 8;
	while (i < bytes_len)
	{
		if (start_index + i >= MEM_SIZE)
			start_index = -i;
		vm->area[start_index + i] = value >> dec;
		i++;
		dec -=8;
	}
}

/*
  ** Return the value of param according to his type.
  ** reg -> reg[param - 1]
  ** dir -> param
  ** ind -> read_next_uint(vm, proc->pc + param, 4)
*/
int		get_param_value(t_vm *vm, t_node *proc, int param[2], int mod)
{
	int addr;

	if (param[1] == DIR_CODE)
		return (param[0]);
	else if (param[1] == REG_CODE)
		return (proc->reg[param[0] - 1]);
	else if (param[1] == IND_CODE)
	{
		if (mod)
			addr = (proc->pc + param[0]) % (proc->pc_b + IDX_MOD);
		else 
			addr = (proc->pc + param[0]) % MEM_SIZE;
		addr = addr < 0 ? MEM_SIZE -(-addr) : addr;
		addr %= MEM_SIZE;
		return (read_next_uint(vm, addr, 4));
	}
	return (-1);
}

/*
  ** Return the champion with num 'champ_num' or null.
*/
t_chmp	*get_chmp_by_num(t_cor *cor, int champ_num)
{
	int i;

	i = -1;
	while (++i < MAX_PLAYERS && cor->chmp[i])
	{
		if (cor->chmp[i]->num == champ_num)
		{
			cor->chmp[i]->last_live = cor->vm->cycle;
			//cor->vm->nb_live++;
			return (cor->chmp[i]);
		}
	}
	return (NULL);
}

void	i_live(t_node *proc, t_cor *cor)
{
	int 	champ_num;
	t_chmp	*chmp;

	champ_num = read_next_uint(cor->vm, proc->pc + 1, 4);

	if (!proc->op.name)
	{
		if (champ_num <= cor->proc->len)
			adv(cor->vm, proc->pc, proc->op_size);
		return ;
	}

	proc->last_live = cor->vm->cycle;
	if (cor->vm->verbose == 1)
		ft_printf("P% 5d | live %d\n", proc->num, champ_num);
	if (!(chmp = get_chmp_by_num(cor, champ_num)))
	{
		if (cor->vm->verbose)
			adv(cor->vm, proc->pc, proc->op_size);
		return ;
	}
	if (cor->vm->verbose)
	{
		ft_printf("Player %d (%s) is said to be alive\n", -chmp->num, chmp->name);
		adv(cor->vm, proc->pc, proc->op_size);
	}
	cor->vm->chmp_win_num = champ_num;
	cor->vm->nb_live++;
}

// Should be ok
void	i_sti(t_node *proc, t_vm *vm)
{
	int addr;
	int	p1;
	int p2;
	int	p3;

	if (!is_regnum_valid(proc->param[0][0] - 1) || !proc->op.name)
	{
		adv(vm, proc->pc, proc->op_size);
		return ;
	}
	if (proc->param[1][1] == REG_CODE && !is_regnum_valid(proc->param[1][0] - 1))
		return ;
	if (proc->param[2][1] == REG_CODE && !is_regnum_valid(proc->param[2][0] - 1))
		return ;

	addr = 0;
	p1 = get_param_value(vm, proc, proc->param[1], 1);
	p2 = get_param_value(vm, proc, proc->param[2], 1);
	p3 = get_param_value(vm, proc, proc->param[0], 1);
	addr = (proc->pc + p1 + p2) % (MEM_SIZE);
	addr = addr < 0 ? MEM_SIZE -(-addr) : addr;
	//addr %= MEM_SIZE;
	write_uint(vm, p3, addr, REG_SIZE);

	if (vm->verbose == 1)
	{
		ft_printf("P    %d | sti r%d %d %d\n", proc->num, proc->param[0][0], p1, p2);
		ft_printf("       | -> store to %d + %d = %d (with pc and mod %d)\n", p1, p2, p1 + p2, addr);
		adv(vm, proc->pc, proc->op_size);
	}
}

void	i_zjmp(t_node *proc, t_vm *vm)
{
	int p1;

	p1 = get_param_value(vm, proc, proc->param[0], 1);
	if (proc->carry)
	{
		proc->op_size = p1 % (proc->pc_b + MEM_SIZE);
		if (vm->verbose == 1)
			ft_printf("P% 5d | zjmp %d OK\n", proc->num, proc->op_size);
		proc->op_size = proc->op_size < 0 ? MEM_SIZE -(-(proc->op_size)) : proc->op_size;
	}
	else if (vm->verbose == 1)
			ft_printf("P% 5d | zjmp %d FAILED\n", proc->num, p1 % (proc->pc_b + MEM_SIZE));
}

// Should be ok
void	i_ldi(t_node *proc, t_vm *vm)
{
	int p1;
	int p2;
	int addr;

	if (proc->param[0][1] == REG_CODE && !is_regnum_valid(proc->param[0][0] - 1))
	{
		adv(vm, proc->pc, proc->op_size);	
		return ;
	}
	if (proc->param[1][1] == REG_CODE && !is_regnum_valid(proc->param[1][0] - 1))
	{
		adv(vm, proc->pc, proc->op_size);	
		return ;
	}
	if (!is_regnum_valid(proc->param[2][0] - 1))
	{
		adv(vm, proc->pc, proc->op_size);
		return ;
	}
	p1 = get_param_value(vm, proc, proc->param[0], 1);
	p2 = get_param_value(vm, proc, proc->param[1], 1);
	addr = (proc->pc + p1 + p2) % (proc->pc_b + IDX_MOD);
	addr = addr < 0 ? MEM_SIZE -(-addr) : addr;
	//addr %= MEM_SIZE;
	proc->reg[proc->param[2][0] - 1] = read_next_uint(vm, addr, REG_SIZE);

	if (vm->verbose)
	{
		ft_printf("P    %d | ldi %d %d r%d\n", proc->num, p1, p2, proc->param[2][0]);
		ft_printf("       | -> load from %d + %d = %d (with pc and mod %d)\n", p1, p2, p1 + p2, addr);
		adv(vm, proc->pc, proc->op_size);
	}
}

void	i_lldi(t_node *proc, t_vm *vm)
{
	int p1;
	int p2;
	int addr;

	if (proc->param[0][1] == REG_CODE && !is_regnum_valid(proc->param[0][0] - 1))
		return ;
	if (proc->param[1][1] == REG_CODE && !is_regnum_valid(proc->param[1][0] - 1))
		return ;
	if (!is_regnum_valid(proc->param[2][0] - 1))
		return ;

	p1 = get_param_value(vm, proc, proc->param[0], 0);
	p2 = get_param_value(vm, proc, proc->param[1], 0);
	addr = (proc->pc + p1 + p2) % MEM_SIZE;
	addr = addr < 0 ? MEM_SIZE -(-addr) : addr;
	//addr %= MEM_SIZE;
	proc->reg[proc->param[2][0] - 1] = read_next_uint(vm, addr, REG_SIZE);
	proc->carry = !proc->reg[proc->param[2][0] - 1];
}

void	i_st(t_node *proc, t_vm *vm)
{
	int p1;
	int	p2;
	int addr;

	if (!is_regnum_valid(proc->param[0][0] - 1) || !proc->op.name)
	{
		adv(vm, proc->pc, proc->op_size);
		return ;
	}
	p1 = get_param_value(vm, proc, proc->param[0], 1);
	p2 = proc->param[1][0];
	if (proc->param[1][1] == IND_CODE)
	{
		addr = proc->pc + (p2 % IDX_MOD); 
		addr = addr < 0 ? MEM_SIZE -(-addr) : addr;
		addr %= MEM_SIZE;
		write_uint(vm, p1, addr, REG_SIZE);
	}
	else if (proc->param[1][1] == REG_CODE)
	{
		if (!is_regnum_valid(p2 - 1))
			return ;
		proc->reg[p2 - 1] = p1;
	}
	if (vm->verbose == 1)
	{
		ft_printf("P% 5d | st r%d %d\n", proc->num, proc->param[0][0], p2);
		adv(vm, proc->pc, proc->op_size);
	}
}

// Should be ok
void	i_add(t_node *proc, t_vm *vm)
{
	int p1;
	int p2;

	if (!is_regnum_valid(proc->param[0][0] - 1) ||
		!is_regnum_valid(proc->param[1][0] - 1) ||
		!is_regnum_valid(proc->param[2][0] - 1))
	{
		adv(vm, proc->pc, proc->op_size);
		return ;
	}

	p1 = get_param_value(vm, proc, proc->param[0], 1);
	p2 = get_param_value(vm, proc, proc->param[1], 1);
	proc->reg[proc->param[2][0] - 1] = p1 + p2;
	proc->carry = !proc->reg[proc->param[2][0] - 1];

	if (vm->verbose)
	{
		ft_printf("P    %d | add r%d r%d r%d\n", proc->num, proc->param[0][0], proc->param[1][0], proc->param[2][0]);
		adv(vm, proc->pc, proc->op_size);
	}
}

// Should be ok
void	i_sub(t_node *proc, t_vm *vm)
{
	int p1;
	int p2;

	if (!is_regnum_valid(proc->param[0][0] - 1) || !is_regnum_valid(proc->param[1][0] - 1) || !is_regnum_valid(proc->param[2][0] - 1))
	{
		adv(vm, proc->pc, proc->op_size);
		return ;
	}

	p1 = get_param_value(vm, proc, proc->param[0], 1);
	p2 = get_param_value(vm, proc, proc->param[1], 1);
	proc->reg[proc->param[2][0] - 1] = p1 - p2;
	proc->carry = !proc->reg[proc->param[2][0] - 1];

	if (vm->verbose == 1)
	{
		ft_printf("P    %d | sub r%d r%d r%d\n", proc->num, proc->param[0][0], proc->param[1][0], proc->param[2][0]);
		adv(vm, proc->pc, proc->op_size);
	}
}

// Should be ok
void	i_and(t_node *proc, t_vm *vm)
{
	int p1;
	int p2;

	if (proc->param[0][1] == REG_CODE && !is_regnum_valid(proc->param[0][0] - 1))
		return ;
	if (proc->param[1][1] == REG_CODE && !is_regnum_valid(proc->param[1][0] - 1))
		return ;
	if (!is_regnum_valid(proc->param[2][0] - 1))
		return ;

	p1 = get_param_value(vm, proc, proc->param[0], 1);
	p2 = get_param_value(vm, proc, proc->param[1], 1);
	proc->reg[proc->param[2][0] - 1] = p1 & p2;
	proc->carry = !proc->reg[proc->param[2][0] - 1];
}

// Should be ok
void	i_or(t_node *proc, t_vm *vm)
{
	int p1;
	int p2;

	if (proc->param[0][1] == REG_CODE && !is_regnum_valid(proc->param[0][0] - 1))
		return ;
	if (proc->param[1][1] == REG_CODE && !is_regnum_valid(proc->param[1][0] - 1))
		return ;
	if (!is_regnum_valid(proc->param[2][0] - 1))
		return ;

	p1 = get_param_value(vm, proc, proc->param[0], 1);
	p2 = get_param_value(vm, proc, proc->param[1], 1);
	proc->reg[proc->param[2][0] - 1] = p1 | p2;
	proc->carry = !proc->reg[proc->param[2][0] - 1];
}

// Should be ok
void	i_xor(t_node *proc, t_vm *vm)
{
	int p1;
	int p2;

	if (proc->param[0][1] == REG_CODE && !is_regnum_valid(proc->param[0][0] - 1))
		return ;
	if (proc->param[1][1] == REG_CODE && !is_regnum_valid(proc->param[1][0] - 1))
		return ;
	if (!is_regnum_valid(proc->param[2][0] - 1))
		return ;

	p1 = get_param_value(vm, proc, proc->param[0], 1);
	p2 = get_param_value(vm, proc, proc->param[1], 1);
	proc->reg[proc->param[2][0] - 1] = p1 ^ p2;
	proc->carry = !proc->reg[proc->param[2][0] - 1];
}

void	i_ld(t_node *proc, t_vm *vm)
{
	int p1;

	p1 = get_param_value(vm, proc, proc->param[0], 1);
	if (!is_regnum_valid(proc->param[1][0] - 1))
		return ;
	proc->reg[proc->param[1][0] - 1] = p1;
	proc->carry = !proc->reg[proc->param[1][0] - 1];

	if (vm->verbose == 1)
	{
		ft_printf("P% 5d | ld %d r%d\n", proc->num, p1, proc->param[1][0]);
		adv(vm, proc->pc, proc->op_size);
	}
}

void	i_lld(t_node *proc, t_vm *vm)
{
	int p1;

	if (!is_regnum_valid(proc->param[1][0] - 1))
		return ;

	p1 = get_param_value(vm, proc, proc->param[0], 0);
	proc->reg[proc->param[1][0] - 1] = p1;
	proc->carry = !proc->reg[proc->param[1][0] - 1];
}

/*
  ** Content of register process as ascii char % 256.
*/
char	i_aff(t_node *proc, t_vm *vm)
{
	int p1;

	if (!is_regnum_valid(proc->param[0][0] - 1))
	{
		adv(vm, proc->pc, proc->op_size);
		return (0);
	}
	p1 = get_param_value(vm, proc, proc->param[0], 1);
	adv(vm, proc->pc, proc->op_size);
	return ((unsigned char)(p1 % 256));
}

void	i_fork(t_node *proc, t_cor *cor)
{
	int p1;
	t_node *child;

	p1 = get_param_value(cor->vm, proc, proc->param[0], 1);
	if (!(child = clone_proc(proc)))
		return ;
	child->pc = proc->pc + (p1 % (proc->pc_b + IDX_MOD));
	child->pc_b = child->pc;
	push_front(&(cor->proc), child);
	child->num = cor->proc->len;
	if (cor->vm->verbose == 1)
	{
		ft_printf("P% 5d | fork %d (%d)\n", proc->num, p1, child->pc);
		adv(cor->vm, proc->pc, proc->op_size);
	}
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
	child->num = cor->proc->len;
	if (cor->vm->verbose == 1)
	{
		ft_printf("P    %d | lfork %d (%d)\n", proc->num, p1, child->pc);
		adv(cor->vm, proc->pc, proc->op_size);
	}
}