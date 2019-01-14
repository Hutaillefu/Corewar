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
  ** Read the next instruction.
*/
int     exec_process(t_vm *vm, int index)
{
    if (!vm || !(vm->area))
        return (0);
    while (vm->area[index])
    {
        if ((int)vm->area[index] == 11) // sti
        {
            printf("STI\n");

            //(int)vm->area[index + 1] = octect de codage. 01 11 10 00
            //01 = 1 -> registre == REG_CODE
            //10 = 2 -> direct == DIR_CODE
            //11 = 3 -> indirect == IND_CODE
            printf("Code param 1: %d\n", read_coding_byte((int)vm->area[index + 1], 1));
            printf("Code param 2: %d\n", read_coding_byte((int)vm->area[index + 1], 2));
            printf("Code param 3: %d\n", read_coding_byte((int)vm->area[index + 1], 3));
            //Extract param 
        }
        index++;
    }
    return (1);
}