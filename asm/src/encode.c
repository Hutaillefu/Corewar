/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   encode.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: quruiz <quruiz@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/15 14:38:51 by quruiz       #+#   ##    ##    #+#       */
/*   Updated: 2019/03/18 20:03:21 by quruiz      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/asm.h"

int		handle_params(t_asm *env, t_code *tmp)
{
	int		i;
	int		val;

	i = 0;
	while (i < tmp->op.nb_param)
	{
		val = 64 / ft_recursive_power(4, i);
		if ((tmp->byte & (IND_CODE * val)) == IND_CODE * val)
		{
			if (!handle_indirect(env, tmp, i))
				return (0);
		}
		else if ((tmp->byte & (DIR_CODE * val)) == DIR_CODE * val)
		{
			if (!handle_direct(env, tmp, i))
				return (0);
		}
		else if ((tmp->byte & (REG_CODE * val)) == REG_CODE * val)
		{
			if (!handle_reg(tmp, i))
				return (0);
		}
		i++;
	}
	return (1);
}

int		encode_asm(t_asm *env)
{
	t_code	*tmp;

	if (!env->code)
		return (err_code(SYNTAX_ERROR, NULL, env));
	tmp = env->code;
	while (tmp)
	{
		env->line_nb = tmp->line_nb;
		if (tmp->type == 2)
		{
			if (!handle_params(env, tmp))
				return (err_code(INVALID_PARAM, tmp->token, env));
		}
		tmp = tmp->next;
	}
	return (1);
}
