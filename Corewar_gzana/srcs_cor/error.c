/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   error.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/15 13:37:01 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/15 14:03:34 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/corewar.h"

void    ft_exit(int error)
{
	if (error == 1)
		ft_printf("Error parsing ac < 2 or open == -1\n");
	if (error == 2)
		ft_printf("Error not files '.cor'\n");
	if (error == 3)
		ft_printf("Error: File has too large a code > 682 bytes\n");
	exit(1);
}