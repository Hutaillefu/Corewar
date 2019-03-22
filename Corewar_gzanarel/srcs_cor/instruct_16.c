/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   instruct_16.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/22 20:37:19 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/22 20:59:17 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/corewar.h"

void	i_aff(t_node *proc, t_vm *vm)
{
	int p1;

	if (!is_regnum_valid(proc->param[0][0] - 1) || proc->op.name == NULL)
	{
		if (vm->verbose & V_ADV)
			adv(vm, proc->pc, proc->op_size);
		return ;
	}
	p1 = get_param_value(vm, proc, proc->param[0], 1);
	if (vm->aff)
		ft_printf(&(vm->logs), "Aff: %c\n", p1 % 256);
	if (vm->verbose & V_ADV)
		adv(vm, proc->pc, proc->op_size);
}
