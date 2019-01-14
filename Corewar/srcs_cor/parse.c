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
	return (op_tab[16]);
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
		
	if (op.opcode == 11) // sti
	{
		printf("STI\n");
		coding_byte = (int)vm->area[++index];
		printf("coding byte of STI :%d\n", coding_byte);
		if (read_coding_byte(coding_byte, 1) != 1)
		{
			printf("Param 1 of STI must be REG\n");
			return (0);
		}
		printf("STI 1st param is REG : %d\n", read_next_uint(vm, ++index, 1));
		if (read_coding_byte(coding_byte, 2) == 2) // direct
		{
			printf("STI 2nd param is DIR : %d\n", read_next_uint(vm, ++index, 2));
			index++;
		}
		else if (read_coding_byte(coding_byte, 2) == 1)
		{
			printf("STI 2nd param is REG : %d\n", read_next_uint(vm, ++index, 1));         
		}
		else if (read_coding_byte(coding_byte, 2) == 3)
		{
			printf("STI 2nd param is IND : %d\n", read_next_uint(vm, ++index, 2));
			index++;     
		}

		if (read_coding_byte(coding_byte, 3) == 2) // direct
		{
			printf("STI 3rd param is DIR : %d\n", read_next_uint(vm, ++index, 2));
			index++;
		}
		else if (read_coding_byte(coding_byte, 3) == 1)
		{
			printf("STI 3rd param is REG : %d\n", read_next_uint(vm, ++index, 1));
			}
	}
	return (1);
}