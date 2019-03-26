/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   coding_byte.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/22 19:44:27 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/22 19:52:03 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/corewar.h"

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
	index = index < 0 ? (MEM_SIZE - (-index)) % MEM_SIZE : index % MEM_SIZE;
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
** Return a value that must be compared with *_CODE.
** Index is param num {1, 3}.
*/

int		read_coding_byte(int byte, int index)
{
	if (index < 1 || index > 3)
		return (-1);
	if (index == 1)
		return (byte >> 6);
	if (index == 2)
		return ((byte & 48) >> 4);
	if (index == 3)
		return ((byte & 12) >> 2);
	return (-1);
}

/*
** Return the matching op.
*/

t_op	get_op_by_opcode(int opcode)
{
	int i;

	i = 0;
	while (op_tab[i].name)
	{
		if (op_tab[i].opcode == opcode)
			return (op_tab[i]);
		i++;
	}
	return (op_tab[i]);
}

int		is_codingbyte_valid(t_node *proc, int coding_byte)
{
	int param;
	int mask;

	param = 0;
	while (++param <= proc->op.nb_params)
	{
		mask = proc->op.param_mask[param - 1];
		if (read_coding_byte(coding_byte, param) == IND_CODE &&
		!(1 && (T_IND & mask) == T_IND))
			return (0);
		else if (read_coding_byte(coding_byte, param) == DIR_CODE &&
		!(1 && (T_DIR & mask) == T_DIR))
			return (0);
		else if (read_coding_byte(coding_byte, param) == REG_CODE &&
		!(1 && (T_REG & mask)))
			return (0);
		else if (read_coding_byte(coding_byte, param) == 0)
			return (0);
	}
	return (1);
}

/*
** Return the size of params from codingbyte.
*/

int		get_codingbyte_len(t_node *proc, int coding_byte)
{
	int param;
	int mask;
	int size;

	size = 0;
	param = 0;
	while (++param <= proc->op.nb_params)
	{
		mask = proc->op.param_mask[param - 1];
		if (read_coding_byte(coding_byte, param) == IND_CODE)
			size += 2;
		else if (read_coding_byte(coding_byte, param) == DIR_CODE)
			size += proc->op.dir_size == 0 ? 4 : 2;
		else if (read_coding_byte(coding_byte, param) == REG_CODE)
			size++;
	}
	return (size);
}
