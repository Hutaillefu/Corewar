/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   instructions4.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: htaillef <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/22 14:57:17 by htaillef     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/22 14:57:18 by htaillef    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

/*
  ** Content of register process as ascii char % 256.
*/

void	i_aff(t_node *proc, t_vm *vm)
{
	int p1;

	if (!is_regnum_valid(proc->param[0][0] - 1) || proc->op.name == NULL)
	{
		adv(vm, proc);
		return ;
	}
	p1 = get_param_value(vm, proc, proc->param[0], 1);
	if (vm->aff)
		ft_printf(&(vm->logs), "Aff: %c\n", p1 % 256);
	adv(vm, proc);
}
