/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools_instruct.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/11 13:33:40 by htaillef     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/25 20:09:47 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/corewar.h"

int		is_regnum_valid(int regnum)
{
	return (regnum >= 0 && regnum <= 15);
}

void	adv(t_vm *vm, t_node *p)
{
	int i;

	if (!(vm->verbose & V_ADV))
		return ;
	i = -1;
	if (p->pc == 0)
		ft_printf(&(vm->logs), "ADV %d (0x0000 -> %#06x)", p->op_size,
		(p->pc + p->op_size));
	else
		ft_printf(&(vm->logs), "ADV %d (%#06x -> %#06x)", p->op_size, p->pc,
		(p->pc + p->op_size));
	while (++i < p->op_size)
	{
		ft_printf(&(vm->logs), "%3.2x", vm->area[(p->pc + i) % MEM_SIZE]);
	}
	ft_printf(&(vm->logs), " \n");
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
	start_index = start_index < 0 ? MEM_SIZE - (-start_index) : start_index;
	start_index %= MEM_SIZE;
	i = 0;
	dec = (bytes_len - 1) * 8;
	while (i < bytes_len)
	{
		if (start_index + i >= MEM_SIZE)
			start_index = -i;
		vm->area[start_index + i] = value >> dec;
		i++;
		dec -= 8;
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
			addr = (proc->pc + (param[0] % IDX_MOD));
		else
			addr = (proc->pc + param[0]) % MEM_SIZE;
		addr = addr < 0 ? (MEM_SIZE - (-addr)) % MEM_SIZE : addr % MEM_SIZE;
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
			return (cor->chmp[i]);
		}
	}
	return (NULL);
}
