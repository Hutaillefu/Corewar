/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   verbose.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/07 13:39:34 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/07 14:33:22 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/corewar.h"

int    ft_convert(int d)
{
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
    return (ft_atoi(tmp));
}

void    ft_verbose(t_vm *vm, char *s)
{
    int d;
    int res;

    res = ft_convert(d);
    if ((d = ft_atoi(s)) > 31)
        return ;
    if ((d & 0x00000F) == 1)
        vm->verbose[0][1];
    if ((d & 0x0000F0) == 1)
        vm->verbose[0][1];
    if ((d & 0x000F00) == 1)
        vm->verbose[0][1];
    if ((d & 0x00F000) == 1)
        vm->verbose[0][1];
    if ((d & 0x0F0000) == 1)
        vm->verbose[0][1];
    if ((d & 0xF00000) == 1)
        vm->verbose[0][1];
}