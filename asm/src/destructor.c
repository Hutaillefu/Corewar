/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   destructor.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: quruiz <quruiz@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/16 19:25:08 by quruiz       #+#   ##    ##    #+#       */
/*   Updated: 2019/02/26 15:51:32 by quruiz      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/asm.h"

void	free_code(t_asm *env)
{
	t_code	*tmp1;
	t_code	*tmp2;

	tmp1 = env->code;
	tmp2 = NULL;
	if (tmp1->next)
	{
		while (tmp1->next)
		{
			tmp2 = tmp1->next;
			free(tmp1->token);
			ft_freesplit(tmp1->raw_params);
			free(tmp1);
			tmp1 = tmp2;
		}
	}
	free(tmp1->token);
	ft_freesplit(tmp1->raw_params);
	free(tmp1);
}

void	free_all(t_asm *env)
{
	if (env->code)
		free_code(env);
	free(env->name);
	free(env);
	env = NULL;
}
