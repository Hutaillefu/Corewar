#include "corewar.h"

/*
  ** Return prog_name encoded after magic (unsigned int) on 128 bits from start of champ.
*/
char    *extract_prog_name(t_vm *vm, int start)
{
    if (!vm || !(vm->area))
        return (NULL);
    return (ft_strsub((char *)vm->area, start + sizeof(unsigned int), PROG_NAME_LENGTH + 4));
}

/*
  ** TODO
*/
unsigned int extract_prog_size(t_vm *vm, int start)
{
    if (!vm || !(vm->area))
        return (0);
    int i = start + 2 * sizeof(unsigned int) + PROG_NAME_LENGTH - 1;
    while (++i < 140)
	    printf("%d ", vm->area[i]);
    printf("\n");
    return 1;
}

/*
  ** 
*/
char    *extract_prog_comment(t_vm *vm, int start)
{
    if (!vm || !(vm->area))
        return (NULL);
    return (ft_strsub((char *)vm->area, start + 2 * sizeof(unsigned int) + PROG_NAME_LENGTH + 4, COMMENT_LENGTH + 140)); // why + 140 ?
}