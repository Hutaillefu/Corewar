/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   instructions.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/11 13:33:40 by htaillef     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/15 15:44:58 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

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

int		get_param_value(t_vm *vm, t_chmp *chmp, int param, int type)
{
	if (type == DIR_CODE)
		return (param);
	else if (type == REG_CODE)
		return (vm->reg[param]);
	else if (type == IND_CODE)
		return (read_next_uint(vm, 0 + param, 4)); // 0 must be replace by chmp->pc but already inc
	return (-1);
}

/*
  ** *(i1 + i2) = registre.
*/
void	i_sti(t_chmp *chmp, t_vm *vm)
{
	int addr;
	int	p1;
	int p2;

	addr = 0;
	p1 = get_param_value(vm, chmp, chmp->param[1][0], chmp->param[1][1]);
	p2 = get_param_value(vm, chmp, chmp->param[2][0], chmp->param[2][1]);
	addr += (p1 + p2) % IDX_MOD;
	write_uint(vm, -chmp->param[0][0], addr, REG_SIZE);
}

void	i_ldi(int i1, int i2, int *registre)
{
	int *addr;

	addr = 0;
	addr += (i1 + i2) % IDX_MOD;
	*registre = *addr;
}

void	i_lldi(int i1, int i2, int *registre)
{
	int *addr;

	addr = 0;
	addr += (i1 + i2);
	*registre = *addr;
	// if *registre == 0 -> carry = 1
}

void	i_add(int *r1, int *r2, int *r3)
{
	*r3 = *r1 + *r2;
	// if *r3 == 0 -> carry = 1
}

void	i_sub(int *r1, int *r2, int *r3)
{
	*r3 = *r1 - *r2;
	// if *r3 == 0 -> carry = 1
}

void	i_and(int i1, int i2, int *r)
{
	*r = i1 & i2;
	// if *r == 0 -> carry = 1
}

void	i_or(int i1, int i2, int *r)
{
	*r = i1 | i2;
	// if *r == 0 -> carry = 1
}

void	i_xor(int i1, int i2, int *r)
{
	*r = i1 ^ i2;
	// if *r == 0 -> carry = 1
}

void	i_ld(int i, int *r)
{
	*r = i;
	// if *r == 0 -> carry = 1
}

/*
  ** Content of register r process as ascii char % 256.
*/

char	i_aff(int *r)
{
	return (((unsigned char)*r) % 256);
}