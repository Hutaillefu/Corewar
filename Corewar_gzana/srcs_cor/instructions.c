/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   instructions.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/11 13:33:40 by htaillef     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/16 16:52:46 by gzanarel    ###    #+. /#+    ###.fr     */
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
		vm->area[start_index + i] = value >> dec;
		i++;
		dec -=8;
	}
}

/*
  ** Return the value of param according to his type.
  ** reg -> reg[param]
  ** dir -> param
  ** ind -> read_next_uint(vm, chmp->pc + param, 4)
*/
int		get_param_value(t_vm *vm, t_chmp *chmp, int param, int type)
{
	if (type == DIR_CODE)
		return (param);
	else if (type == REG_CODE)
		return (chmp->reg[param - 1]);
	else if (type == IND_CODE)
		return (read_next_uint(vm, chmp->pc + param, 4));
	return (-1);
}

void	i_sti(t_chmp *chmp, t_vm *vm)
{
	int addr;
	int	p1;
	int p2;
	int	p3;
	addr = 0;
	p1 = get_param_value(vm, chmp, chmp->param[1][0], chmp->param[1][1]);
	p2 = get_param_value(vm, chmp, chmp->param[2][0], chmp->param[2][1]);
	p3 = get_param_value(vm, chmp, chmp->param[0][0], chmp->param[0][1]);
	addr = (chmp->pc + p1 + p2) % (chmp->pc_b + IDX_MOD);
	write_uint(vm, p3, addr, REG_SIZE);
}

void	i_ldi(t_chmp *chmp, t_vm *vm)
{
	int p1;
	int p2;
	int p3;

	p1 = get_param_value(vm, chmp, chmp->param[0][0], chmp->param[0][1]);
	p2 = get_param_value(vm, chmp, chmp->param[1][0], chmp->param[1][1]);
	p3 = get_param_value(vm, chmp, chmp->param[2][0], chmp->param[2][1]);
	chmp->reg[p3] = read_next_uint(vm, (chmp->pc + p1 + p2) % IDX_MOD, REG_SIZE);
}

void	i_lldi(t_chmp *chmp, t_vm *vm)
{
	int p1;
	int p2;
	int p3;

	p1 = get_param_value(vm, chmp, chmp->param[0][0], chmp->param[0][1]);
	p2 = get_param_value(vm, chmp, chmp->param[1][0], chmp->param[1][1]);
	p3 = get_param_value(vm, chmp, chmp->param[2][0], chmp->param[2][1]);
	chmp->reg[p3] = read_next_uint(vm, chmp->pc + p1 + p2, REG_SIZE);
}

void	i_add(t_chmp *chmp, t_vm *vm)
{
	int p1;
	int p2;
	int	p3;

	p1 = get_param_value(vm, chmp, chmp->param[0][0], chmp->param[0][1]);
	p2 = get_param_value(vm, chmp, chmp->param[1][0], chmp->param[1][1]);
	p3 = get_param_value(vm, chmp, chmp->param[2][0], chmp->param[2][1]);
	chmp->reg[p3] = p1 + p2;
	// if *r3 == 0 -> carry = 1
}

void	i_sub(t_chmp *chmp, t_vm *vm)
{
	int p1;
	int p2;
	int	p3;

	p1 = get_param_value(vm, chmp, chmp->param[0][0], chmp->param[0][1]);
	p2 = get_param_value(vm, chmp, chmp->param[1][0], chmp->param[1][1]);
	p3 = get_param_value(vm, chmp, chmp->param[2][0], chmp->param[2][1]);
	chmp->reg[p3] = p1 - p2;
}

void	i_and(t_chmp *chmp, t_vm *vm)
{
	int p1;
	int p2;
	int	p3;

	p1 = get_param_value(vm, chmp, chmp->param[0][0], chmp->param[0][1]);
	p2 = get_param_value(vm, chmp, chmp->param[1][0], chmp->param[1][1]);
	p3 = get_param_value(vm, chmp, chmp->param[2][0], chmp->param[2][1]);
	chmp->reg[p3] = p1 & p2;
}

void	i_or(t_chmp *chmp, t_vm *vm)
{
	int p1;
	int p2;
	int	p3;

	p1 = get_param_value(vm, chmp, chmp->param[0][0], chmp->param[0][1]);
	p2 = get_param_value(vm, chmp, chmp->param[1][0], chmp->param[1][1]);
	p3 = get_param_value(vm, chmp, chmp->param[2][0], chmp->param[2][1]);
	chmp->reg[p3] = p1 | p2;
}

void	i_xor(t_chmp *chmp, t_vm *vm)
{
	int p1;
	int p2;
	int	p3;

	p1 = get_param_value(vm, chmp, chmp->param[0][0], chmp->param[0][1]);
	p2 = get_param_value(vm, chmp, chmp->param[1][0], chmp->param[1][1]);
	p3 = get_param_value(vm, chmp, chmp->param[2][0], chmp->param[2][1]);
	chmp->reg[p3] = p1 ^ p2;
}

void	i_ld(t_chmp *chmp, t_vm *vm)
{
	int p1;
	int p2;

	p1 = get_param_value(vm, chmp, chmp->param[0][0], chmp->param[0][1]);
	p2 = get_param_value(vm, chmp, chmp->param[1][0], chmp->param[1][1]);
	chmp->reg[p2] = p1;
}

/*
  ** Content of register r process as ascii char % 256.
*/

char	i_aff(int *r)
{
	return (((unsigned char)*r) % 256);
}