/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   instructions.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/11 13:33:40 by htaillef     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/17 18:20:28 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

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
  ** ind -> read_next_uint(vm, chmp->pc + param, 4)
*/
int		get_param_value(t_vm *vm, t_chmp *chmp, int param[2], int mod)
{
	int addr;

	if (param[1] == DIR_CODE)
		return (param[0]);
	else if (param[1] == REG_CODE)
		return (chmp->reg[param[0] - 1]);
	else if (param[1] == IND_CODE)
	{
		if (mod)
			addr = (chmp->pc + param[0]) % (chmp->pc_b + IDX_MOD);
		else 
			addr = (chmp->pc + param[0]) % MEM_SIZE;
		addr = addr < 0 ? MEM_SIZE -(-addr) : addr;
		return (read_next_uint(vm, addr, 4));
	}
	return (-1);
}

/*
  ** Return the champion with num 'champ_num' or null.
*/
t_chmp	*get_chmp_by_num(t_cor 	*cor, int champ_num)
{
	int i;

	i = -1;
	while (++i < MAX_PLAYERS && cor->chmp[i])
	{
		if (cor->chmp[i]->num == champ_num)
			return (cor->chmp[i]);
	}
	return (NULL);
}

void	i_live(t_chmp *chmp, t_cor *cor)
{
	int 	champ_num;
	t_chmp	*selected_chmp;

	champ_num = read_next_uint(cor->vm, chmp->pc + 1, 4);
	if (!(selected_chmp = get_chmp_by_num(cor, champ_num)))
		return ;
	selected_chmp->lives++;
	selected_chmp->last_live = cor->vm->cycle;
}

// Should be ok
void	i_sti(t_chmp *chmp, t_vm *vm)
{
	int addr;
	int	p1;
	int p2;
	int	p3;
	addr = 0;
	p1 = get_param_value(vm, chmp, chmp->param[1], 1);
	p2 = get_param_value(vm, chmp, chmp->param[2], 1);
	p3 = get_param_value(vm, chmp, chmp->param[0], 1);
	addr = (chmp->pc + p1 + p2) % (chmp->pc_b + IDX_MOD);
	addr = addr < 0 ? MEM_SIZE -(-addr) : addr;
	write_uint(vm, p3, addr, REG_SIZE);
}

// Should be ok
void	i_ldi(t_chmp *chmp, t_vm *vm)
{
	int p1;
	int p2;
	int addr;

	p1 = get_param_value(vm, chmp, chmp->param[0], 1);
	p2 = get_param_value(vm, chmp, chmp->param[1], 1);
	addr = (chmp->pc + p1 + p2) % (chmp->pc_b + IDX_MOD);
	addr = addr < 0 ? MEM_SIZE -(-addr) : addr;
	chmp->reg[chmp->param[2][0] - 1] = read_next_uint(vm, addr, REG_SIZE);
}

void	i_lldi(t_chmp *chmp, t_vm *vm)
{
	int p1;
	int p2;

	p1 = get_param_value(vm, chmp, chmp->param[0], 0);
	p2 = get_param_value(vm, chmp, chmp->param[1], 0);
	chmp->reg[chmp->param[2][0] - 1] = read_next_uint(vm, (chmp->pc + p1 + p2) % MEM_SIZE, REG_SIZE);
}

// Should be ok
void	i_add(t_chmp *chmp, t_vm *vm)
{
	int p1;
	int p2;

	p1 = get_param_value(vm, chmp, chmp->param[0], 1);
	p2 = get_param_value(vm, chmp, chmp->param[1], 1);
	chmp->reg[chmp->param[2][0] - 1] = p1 + p2;
	//chmp->carry = chmp->reg[chmp->param[2][0] - 1] == 0; How to manage carry ?
}

// Should be ok
void	i_sub(t_chmp *chmp, t_vm *vm)
{
	int p1;
	int p2;

	p1 = get_param_value(vm, chmp, chmp->param[0], 1);
	p2 = get_param_value(vm, chmp, chmp->param[1], 1);
	chmp->reg[chmp->param[2][0] - 1] = p1 - p2;
}

// Should be ok
void	i_and(t_chmp *chmp, t_vm *vm)
{
	int p1;
	int p2;

	p1 = get_param_value(vm, chmp, chmp->param[0], 1);
	p2 = get_param_value(vm, chmp, chmp->param[1], 1);
	chmp->reg[chmp->param[2][0] - 1] = p1 & p2;
}

// Should be ok
void	i_or(t_chmp *chmp, t_vm *vm)
{
	int p1;
	int p2;

	p1 = get_param_value(vm, chmp, chmp->param[0], 1);
	p2 = get_param_value(vm, chmp, chmp->param[1], 1);
	chmp->reg[chmp->param[2][0] - 1] = p1 | p2;
}

// Should be ok
void	i_xor(t_chmp *chmp, t_vm *vm)
{
	int p1;
	int p2;

	p1 = get_param_value(vm, chmp, chmp->param[0], 1);
	p2 = get_param_value(vm, chmp, chmp->param[1], 1);
	chmp->reg[chmp->param[2][0] - 1] = p1 ^ p2;
}

void	i_ld(t_chmp *chmp, t_vm *vm)
{
	int p1;

	printf("Execute ld\n");
	p1 = get_param_value(vm, chmp, chmp->param[0], 1);
	printf("LD param is %d\n", p1);
	chmp->reg[chmp->param[1][0] - 1] = p1;
}

void	i_lld(t_chmp *chmp, t_vm *vm)
{
	int p1;

	p1 = get_param_value(vm, chmp, chmp->param[0], 0);
	chmp->reg[chmp->param[1][0] - 1] = p1;
}

/*
  ** Content of register process as ascii char % 256.
*/

char	i_aff(t_chmp *chmp, t_vm *vm)
{
	int p1;

	p1 = get_param_value(vm, chmp, chmp->param[0], 1);
	return ((unsigned char)(p1 % 256));
}