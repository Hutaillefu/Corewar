/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   instructions.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/11 13:33:40 by htaillef     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/22 11:19:49 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

int		is_regnum_valid(int regnum)
{
	return (regnum >= 0 && regnum <= 15);
}

void	adv(t_vm *vm, t_node *p)
{
	int i;

	if (!vm || !p || !(vm->verbose & V_ADV))
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
  ** Read the next int from index coded on bytes_len.
*/

int		read_next_uint(t_vm *vm, int index, int bytes_len)
{
	int				i;
	int				dec;
	unsigned int	res;

	if (!vm)
		return (0);
	i = 0;
	res = 0;
	dec = (bytes_len - 1) * 8;
	while (i < bytes_len)
	{
		if (index + i >= MEM_SIZE)
			index = -i;
		res |= vm->area[index + i] << dec;
		i++;
		dec -= 8;
	}
	return (res);
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
