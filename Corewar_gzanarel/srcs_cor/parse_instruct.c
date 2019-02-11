#include "corewar.h"

/*
  ** Read the next int from index coded on bytes_len.
*/
int    read_next_uint(t_vm *vm, int index, int bytes_len)
{
	int	i;
	int dec;
	unsigned int res;

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
		dec -=8;
	}
	return (res);
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
		{
			return (op_tab[i]);
		}
		i++;
	}
	return (op_tab[i]);
}

/*
  ** Setup op params for the given chmp.
*/
int		extract_param(t_vm *vm, t_node *proc, int param_index, int coding_byte)
{
	int	mask;
	int res;
	
	if (!vm || !proc)
		return (0);

	mask = proc->op.param_mask[param_index];
	if (coding_byte != -1 ? read_coding_byte(coding_byte, param_index + 1) == REG_CODE : 1 && (T_REG & mask))
	{
		res = read_next_uint(vm, proc->pc, 1);
		proc->param[param_index][0] = res;
		proc->param[param_index][1] = REG_CODE;
		(proc->pc)++;
		return (1);
	}
	else if (coding_byte != -1 ? read_coding_byte(coding_byte, param_index + 1) == DIR_CODE : 1 && (T_DIR & mask) == T_DIR)
	{
		if (proc->op.dir_size == 0)
			res = read_next_uint(vm, proc->pc, 4);
		else
			res = (short)read_next_uint(vm, proc->pc, 2);		
		proc->param[param_index][0] = res;
		proc->param[param_index][1] = DIR_CODE;
		proc->pc += proc->op.dir_size == 0 ? 4 : 2;
		return (1);
	}
	else if (coding_byte != -1 ? read_coding_byte(coding_byte, param_index + 1) == IND_CODE : 1 && (T_IND & mask) == T_IND)
	{
		res = (short)read_next_uint(vm, proc->pc, 2);
		proc->param[param_index][0] = res;
		proc->param[param_index][1] = IND_CODE;
		proc->pc += 2;
		return (1);
	}
	return (0);
}

/*
  ** Initializes param to default value.
*/
void	init_param(t_node *proc)
{
	if (!proc)
		return ;
	proc->op_size = 0;
	proc->param[0][0] = -1;
	proc->param[0][1] = -1;
	proc->param[1][0] = -1;
	proc->param[1][1] = -1;
	proc->param[2][0] = -1;
	proc->param[2][1] = -1;
}

int 	check_coding_byte(t_node *proc, int coding_byte)
{
	int param;
	int mask;

	param = 0;
	while (++param <= proc->op.nb_params)
	{
		mask = proc->op.param_mask[param - 1];
		if ((read_coding_byte(coding_byte, param) == IND_CODE))
		{
			if (!(1 && (T_IND & mask) == T_IND))
				return (2);
			else
				proc->op_size += 2;
		}
		if ((read_coding_byte(coding_byte, param) == DIR_CODE))
		{
			if (!(1 && (T_DIR & mask) == T_DIR))
				return (2);
			else 
				proc->op_size += proc->op.dir_size == 0 ? 4 : 2;
		}
		if ((read_coding_byte(coding_byte, param) == REG_CODE))
		{
			if (!(1 && (T_REG & mask)))
				return (2);
			else
				proc->op_size += 2;
		}
	}
	return (1);
}

int		extract_params(t_vm *vm, t_node *proc, int coding_byte)
{
	if (!vm || !(vm->area) || !(proc))
		return (0);
	init_param(proc);
	if (check_coding_byte(proc, coding_byte) == 2)
		proc->op.coding_byte = -1;
	if (proc->op.nb_params >= 1 && !extract_param(vm, proc, 0, coding_byte))
	{
		//printf("error 1 param\n");
		return (0);
	}
	if (proc->op.nb_params >= 2 && !extract_param(vm, proc, 1, coding_byte))
	{
		//printf("error 2 param\n");
		return (0);
	}
	if (proc->op.nb_params == 3 && !extract_param(vm, proc, 2, coding_byte))
		return (0);
	return (1);
}

/*
  ** Read the next instruction.
*/
int     exec_process(t_vm *vm, t_node *proc)
{
	int		coding_byte;
	int		pc_base;
	t_op	op;

	if (!vm || !(vm->area) || !proc)
		return (0);
	pc_base = proc->pc;
	if (!(op = get_op_by_opcode((int)vm->area[proc->pc])).name)
	{
		proc->exec = 0;
		return (0);
	}
	proc->op = op;
	coding_byte = -1;
	if (op.coding_byte)
		coding_byte = (int)vm->area[++(proc->pc)];
	(proc->pc)++;
	if (!extract_params(vm, proc, coding_byte))
	{
		// printf("Extract params error for instruction %s with %d params\n", op.name, op.nb_params);
		return (0);
	}
	proc->op_size = proc->pc - pc_base;
	proc->pc = pc_base;
	return (1);
}