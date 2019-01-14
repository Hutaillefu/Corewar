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
  ** TODO
*/
unsigned int extract_prog_size(t_vm *vm)
{
    unsigned int    size;
    int             index;

    if (!vm || !(vm->area))
        return (0);
    index = sizeof(unsigned int) * 2 + PROG_NAME_LENGTH;
    size = 0;
    size |= (int)vm->area[index] << 24;
    size |= (int)vm->area[index + 1] << 16;
    size |= (int)vm->area[index + 2] << 8;
    size |= (int)vm->area[index + 3];
    return (size);
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