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
			return (op_tab[i]);
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
		proc->pc = (proc->pc + 1) % MEM_SIZE;
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
		proc->pc = (proc->pc + (proc->op.dir_size == 0 ? 4 : 2)) % MEM_SIZE;
		return (1);
	}
	else if (coding_byte != -1 ? read_coding_byte(coding_byte, param_index + 1) == IND_CODE : 1 && (T_IND & mask) == T_IND)
	{
		res = (short)read_next_uint(vm, proc->pc, 2);
		proc->param[param_index][0] = res;
		proc->param[param_index][1] = IND_CODE;
		proc->pc = (proc->pc + 2) % MEM_SIZE;
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

int		extract_params(t_vm *vm, t_node *proc, int coding_byte)
{
	if (!vm || !(vm->area) || !(proc))
		return (0);
	init_param(proc);
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
  ** Return true if codingbyte is valid, else false.
*/
int 	is_codingbyte_valid(t_node *proc, int coding_byte)
{
	int param;
	int mask;

	param = 0;
	while (++param <= proc->op.nb_params)
	{
		mask = proc->op.param_mask[param - 1];
		if (read_coding_byte(coding_byte, param) == IND_CODE && !(1 && (T_IND & mask) == T_IND))
			return (0);
		else if (read_coding_byte(coding_byte, param) == DIR_CODE && !(1 && (T_DIR & mask) == T_DIR))
			return (0);
		else if (read_coding_byte(coding_byte, param) == REG_CODE && !(1 && (T_REG & mask)))
			return (0);
		else if (read_coding_byte(coding_byte, param) == 0)
			return (0);
	}
	return (1);
}

/*
  ** Return the size of params from codingbyte.
*/
int 	get_codingbyte_len(t_node *proc, int coding_byte)
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

int		load(t_vm *vm, t_node *proc)
{
	t_op	op;
	int		coding_byte;
	int		pc_base;

	pc_base = proc->pc;

	proc->op.coding_byte = -1;
	proc->op.nb_cycles = 1;
	proc->op.opcode = -1;
	proc->op.name = NULL;
	proc->op.nb_params = 0;

	if (!(op = get_op_by_opcode((int)vm->area[proc->pc])).name)
	{
		proc->op.opcode = -1;
		proc->op_size = 1;
		return (0);
	}
	proc->op = op;
	coding_byte = -1;
	if (op.coding_byte)
		coding_byte = (int)vm->area[++(proc->pc) % MEM_SIZE];

	// if ( (proc->num == 2074 || proc->num == 1746 || proc->num == 964 || proc->num == 640 || proc->num == 263) 
	// 	&& vm->cycle == 25340)
	// 	ft_printf(&(vm->logs), "proc num %d previous coding byte was %d\n", proc->num, coding_byte);


	if (op.coding_byte && !is_codingbyte_valid(proc, coding_byte))
	{
		proc->pc = pc_base;
		proc->op_size = get_codingbyte_len(proc, coding_byte) + 1 + 1;
		return (0);
	}
	proc->pc = (proc->pc + 1) % MEM_SIZE;
	extract_params(vm, proc, coding_byte);
	proc->op_size = proc->pc - pc_base;
	proc->pc = pc_base;

	return (1);

}

int		exec(t_vm *vm, t_node *proc)
{
	int		coding_byte;
	int		pc_base;

	// if (proc->op.opcode != vm->area[proc->pc])
	// 	ft_printf(&(vm->logs), "%d -> %d\n", proc->op.opcode, vm->area[proc->pc]);

	pc_base = proc->pc;
	coding_byte = -1;
	if (proc->op.coding_byte > 0)
	{
		coding_byte = (int)vm->area[++(proc->pc) % MEM_SIZE];
		if (!is_codingbyte_valid(proc, coding_byte))
		{
		
			proc->op.name = NULL;
			proc->pc = pc_base;
			proc->op_size = get_codingbyte_len(proc, coding_byte) + 1 + 1;
			return (0);
		}
	}
	
	proc->pc = (proc->pc + 1) % MEM_SIZE;
	extract_params(vm, proc, coding_byte);
	proc->op_size = proc->pc < pc_base ? (MEM_SIZE - pc_base + proc->pc) : proc->pc - pc_base;
	proc->pc = pc_base;

	return (1);
}
