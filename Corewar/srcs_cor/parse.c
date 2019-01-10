#include "corewar.h"

/*
  ** Return prog_name encoded after magic (unsigned int) on 128 bits from start of champ.
*/
char    *extract_prog_name(t_vm *vm, int start)
{
    if (!vm || !(vm->area))
        return (NULL);
    return (ft_strsub((char *)vm->area, start + sizeof(unsigned int), PROG_NAME_LENGTH));
}

/*
  ** TODO
*/
unsigned int extract_prog_size(t_vm *vm)
{
    if (!vm || !(vm->area))
        return (0);
    return 1;
}

/*
  ** DOESNT WORK
*/
char    *extract_prog_comment(t_vm *vm, int start)
{
    if (!vm || !(vm->area))
        return (NULL);
    return (ft_strsub((char *)vm->area, start + 8 + PROG_NAME_LENGTH, COMMENT_LENGTH));
}