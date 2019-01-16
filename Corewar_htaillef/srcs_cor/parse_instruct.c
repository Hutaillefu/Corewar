#include "corewar.h"

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
  ** Setup op params for the given chmp.
*/
int		extract_param(t_vm *vm, t_chmp *chmp, int param_index, int coding_byte)
{
	int	mask;
	int res;
	
	if (!vm || !chmp)
		return (0);
	mask = chmp->op.param_mask[param_index];
	if (read_coding_byte(coding_byte, param_index + 1) == REG_CODE && (REG_CODE & mask)) // octect codage indique REG et op_tab aussi
	{
		res = read_next_uint(vm, chmp->pc, 1);
		chmp->param[param_index][0] = res;
		chmp->param[param_index][1] = REG_CODE;
		(chmp->pc)++;
		return (1);
	}
	else if (read_coding_byte(coding_byte, param_index + 1) == DIR_CODE && (DIR_CODE & mask) == DIR_CODE)
	{
		res = read_next_uint(vm, chmp->pc, chmp->op.dir_size == 0 ? 4 : 2);
		chmp->param[param_index][0] = res;
		chmp->param[param_index][1] = DIR_CODE;
		chmp->pc += chmp->op.dir_size == 0 ? 4 : 2;
		return (1);
	}
	else if (read_coding_byte(coding_byte, param_index + 1) == IND_CODE && (IND_CODE & mask) == IND_CODE)
	{
		res = read_next_uint(vm, chmp->pc, 2);
		chmp->param[param_index][0] = res;
		chmp->param[param_index][1] = IND_CODE;
		chmp->pc += 2;
		return (1);
	}
	return (0);
}

/*
  ** Initializes param to default value.
*/
void	init_param(t_chmp *chmp)
{
	if (!chmp)
		return ;
	chmp->op_size = 0;
	chmp->param[0][0] = -1;
	chmp->param[0][1] = -1;
	chmp->param[1][0] = -1;
	chmp->param[1][1] = -1;
	chmp->param[2][0] = -1;
	chmp->param[2][1] = -1;
}

int		extract_params(t_vm *vm, t_chmp *chmp, int coding_byte)
{
	if (!vm || !(vm->area) || !(chmp))
		return (0);
	if (coding_byte == -1)
		return 23; // process non byte coding : live, lfork, ..
	init_param(chmp);
	if (chmp->op.nb_params >= 1 && !extract_param(vm, chmp, 0, coding_byte))
		return (0);
	if (chmp->op.nb_params >= 2 && !extract_param(vm, chmp, 1, coding_byte))
		return (0);
	if (chmp->op.nb_params == 3 && !extract_param(vm, chmp, 2, coding_byte))
		return (0);
	return (1);
}

/*
  ** Read the next instruction.
*/
int     exec_process(t_vm *vm, t_chmp *chmp)
{
	int		coding_byte;
	int		pc_base;
	t_op	op;

	if (!vm || !(vm->area) || !chmp)
		return (0);
	pc_base = chmp->pc;
	if (!(op = get_op_by_opcode((int)vm->area[chmp->pc])).name)
		return (0);
	chmp->op = op;
	coding_byte = -1;
	if (op.coding_byte)
		coding_byte = (int)vm->area[++(chmp->pc)];
	(chmp->pc)++;
	if (!extract_params(vm, chmp, coding_byte))
		return (0);
	chmp->op_size = chmp->pc - pc_base;
	chmp->pc = pc_base;
	return (1);
}