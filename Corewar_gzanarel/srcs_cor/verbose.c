/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   verbose.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/07 13:39:34 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/07 15:48:34 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/corewar.h"

int    ft_convert(int d)
{
    int tmp;
    char s[2];
    int i;

    i = 0;
    while (d != 0)
    {
        tmp = 0;
        tmp = d % 16;
        if (tmp < 10)
            s[i] = tmp + 48;
        else
            s[i] = tmp + 55;
        i++;
        d = d / 16;
    }
    return (ft_atoi(s));
}

void    init_verbose(int verbose[6])
{
    int a;

    a = -1;
    while (verbose[++a] < 6)
        verbose[a] = 0;
}

int     get_in_bit(char verbose, const char index)
{
    if (verbose > 31 || (index < 0 || index > 7))
        return (0);
    return ((verbose >> index) & 1);
}

// void    ft_verbose(t_vm *vm, char *s)
// {
//     int d;

//     if ((d = ft_atoi(s)) > 31)
//         return ;
//     d = ft_convert(d);
//     init_verbose(vm->verbose);
//     if ((d & 0x0000000000FF) == 1)
//         vm->verbose[0] = 1;
//     if ((d & 0x00000000FF00) == 1)
//         vm->verbose[1] = 1;
//     if ((d & 0x000000FF0000) == 1)
//         vm->verbose[2] = 1;
//     if ((d & 0x0000FF000000) == 1)
//         vm->verbose[3] = 1;
//     if ((d & 0x00FF00000000) == 1)
//         vm->verbose[4] = 1;
//     if ((d & 0xFF0000000000) == 1)
//         vm->verbose[5] = 1;
// }
