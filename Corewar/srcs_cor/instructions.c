/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   instructions.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: htaillef <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/11 13:33:40 by htaillef     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/11 13:33:41 by htaillef    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

/*
  ** *(i1 + i2) = registre.
*/
void	i_sti(int *registre, int i1, int i2)
{
	int *addr;

	addr = 0;
	addr += i1 + i2;
	*addr = *registre;
}

void	i_ldi(int i1, int i2, int *registre)
{
	int *addr;

	addr = 0;
	addr += i1 + i2;
	*registre = *addr;
}

void	i_add(int *r1, int *r2, int *r3)
{
	*r3 = *r1 + *r2;
	// if *r3 == 0 -> carry = 1
}

void	i_sub(int *r1, int *r2, int *r3)
{
	*r3 = *r1 - *r2;
}

void	i_and(int i1, int i2, int *r)
{
	*r = i1 & i2;
}

void	i_ld(int i, int *r)
{
	*r = i;
}