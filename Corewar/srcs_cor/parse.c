#include "corewar.h"

/*
  ** Return prog_name encoded after magic (unsigned int) on 128 bits from start of champ.
*/
char    *extract_prog_name(t_vm *vm)
{
	if (!vm || !(vm->area))
		return (NULL);
	return (ft_strsub((char *)vm->area, sizeof(unsigned int), PROG_NAME_LENGTH));
}

/*
  ** Read the next int from index coded on bytes_len.
*/
int    read_next_uint(t_vm *vm, int index, int bytes_len)
{
	unsigned int res;

	res = 0;
	if (bytes_len == 1)
		return (res | (int)vm->area[index]);
	else if (bytes_len == 2)
		return (res | (int)vm->area[index] << 8 | (int)vm->area[index + 1]);
	else if (bytes_len == 4)
		return (res | (int)vm->area[index] << 24 |
		(int)vm->area[index + 1] << 16 |
		(int)vm->area[index + 2] << 8 |
		(int)vm->area[index + 3]);
	return (-1);
}

/*
  **
*/
unsigned int extract_prog_size(t_vm *vm)
{
	if (!vm || !(vm->area))
		return (0);
	return (read_next_uint(vm, sizeof(unsigned int) * 2 + PROG_NAME_LENGTH, 4));
}

/*
  ** 
*/
char    *extract_prog_comment(t_vm *vm)
{
	if (!vm || !(vm->area))
		return (NULL);
	return (ft_strsub((char *)vm->area, 3 * sizeof(unsigned int) + PROG_NAME_LENGTH, COMMENT_LENGTH));
}

/*
  ** Return a value that must be compared with *_CODE.
  ** Index is param num {1, 3}.
*/
int     read_coding_byte(int byte, int index)
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
t_op    get_op_by_opcode(int opcode)
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

/*
  ** Should return a struct to keep dir, reg, ind info ?
*/
int		extract_param(t_vm *vm, t_op op, int *index, int param_index, int coding_byte)
{
	int	mask;
	int res;
	
	if (!vm)
		return (-1);
	mask = op.param_mask[param_index];
	if (read_coding_byte(coding_byte, param_index + 1) == REG_CODE && (REG_CODE & mask)) // octect codage indique REG et op_tab aussi
	{
		res = read_next_uint(vm, *index, 1);
		(*index)++;
		return (res);
	}
	else if (read_coding_byte(coding_byte, param_index + 1) == DIR_CODE && (DIR_CODE & mask) == DIR_CODE)
	{
		res = read_next_uint(vm, *index, op.dir_size == 0 ? 4 : 2);
		(*index) += op.dir_size == 0 ? 4 : 2;
		return (res);
	}
	else if (read_coding_byte(coding_byte, param_index + 1) == IND_CODE && (IND_CODE & mask) == IND_CODE)
	{
		res = read_next_uint(vm, *index, 2);
		(*index) += 2;
		return (res);
	}
	return (-1);
}

int		extract_params(t_vm *vm, t_op op, int *index, int coding_byte)
{
	int p1;
	int p2;
	int p3;

	if (!vm || !(vm->area))
		return (-1);
	if (coding_byte == -1)
		return 23; // process non byte coding like live, lfork, ..
	p1 = -1;
	p2 = -1;
	p3 = -1;
	if (op.nb_params >= 1 && (p1 = extract_param(vm, op, index, 0, coding_byte)) == -1)
		return (-1);
	if (op.nb_params >= 2 && (p2 = extract_param(vm, op, index, 1, coding_byte)) == -1)
		return (-1);
	if (op.nb_params == 3 && (p3 = extract_param(vm, op, index, 2, coding_byte)) == -1)
		return (-1);

	printf("P1 : %d\n", p1);
	printf("P2 : %d\n", p2);
	printf("P3 : %d\n", p3);
	
	return (1);
}

/*
  ** Read the next instruction.
*/
int     exec_process(t_vm *vm, int index)
{
	int		coding_byte;
	t_op	op;

	if (!vm || !(vm->area))
		return (0);

	if (!(op = get_op_by_opcode((int)vm->area[index])).name)
		return (0);
	coding_byte = -1;
	if (op.coding_byte)	
		coding_byte = (int)vm->area[++index];
	index++;
	if (extract_params(vm, op, &index, coding_byte) == -1)
	{
		printf("Error extracting params of %s\n", op.name);
		return (0);
	}
	return (1);
}