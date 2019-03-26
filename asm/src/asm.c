/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   asm.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: quruiz <quruiz@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/16 16:58:11 by quruiz       #+#   ##    ##    #+#       */
/*   Updated: 2019/03/23 17:35:39 by quruiz      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/asm.h"

int		main(int argc, char *argv[])
{
	t_asm	*env;

	if (argc != 2)
	{
		err_code(BAD_FILENAME, NULL, NULL);
		return (-1);
	}
	if (!check_file(&env, argv))
		return (-1);
	if (!parse_file(env))
		return (-1);
	if (!encode_asm(env))
		return (-1);
	if (!write_cor(env))
		return (-1);
	free_all(env);
	return (1);
}
