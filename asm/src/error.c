/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   error.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: quruiz <quruiz@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/22 17:21:02 by quruiz       #+#   ##    ##    #+#       */
/*   Updated: 2019/03/28 14:06:02 by quruiz      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/asm.h"

int		err_code(int code, char *tkn, t_asm *env)
{
	if (code == MEM_ERROR)
		ft_printf("Malloc error\n");
	else if (code == BAD_FILENAME)
		ft_printf("Usage: ./asm <file>.s\n");
	else if (code == ERROR_FILE)
		ft_printf("Can't read or create file\n");
	else if (code == SIZE_ERROR)
		ft_printf("%s too long\n", tkn);
	else if (code == SYNTAX_ERROR)
		ft_printf("Syntax error at line %.3d\n", env->line_nb);
	else if (code == INVALID_OP)
		ft_printf("Invalid instruction at line %.3d\n", env->line_nb);
	else if (code == INVALID_PARAM)
		ft_printf("Invalid parameter for %s at line %.3d\n", tkn, env->line_nb);
	else if (code == NO_TOKEN)
		ft_printf("Can't find token \"%s\" at line %.3d\n", tkn, env->line_nb);
	else if (code == LEXICAL_ERROR)
		ft_printf("Lexical error at line %.3d\n", env->line_nb);
	else if (code == NEW_LINE)
		ft_printf("File must end with a empty line\n");
	if (env)
		free_all(env);
	return (0);
}
