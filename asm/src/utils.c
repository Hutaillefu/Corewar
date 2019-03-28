/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: quruiz <quruiz@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/24 21:29:23 by quruiz       #+#   ##    ##    #+#       */
/*   Updated: 2019/03/27 14:06:32 by quruiz      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/asm.h"

int		check_extension(char *file)
{
	int		len;

	len = ft_strlen(file);
	if (!(file[len - 1] == 's' && file[len - 2] == '.'))
		return (0);
	return (1);
}

int		check_file(t_asm **env, char **arg)
{
	if (!check_extension(arg[1]))
		return (err_code(BAD_FILENAME, NULL, NULL));
	if (!(*env = ft_memalloc(sizeof(t_asm))))
		return (err_code(MEM_ERROR, NULL, NULL));
	(*env)->name = ft_strsub(arg[1], 0, (ft_strlen(arg[1]) - 1));
	(*env)->name = ft_conncat((*env)->name, "cor", ft_strlen((*env)->name), 3);
	(*env)->input_fd = open(arg[1], O_RDONLY);
	(*env)->line_nb = 0;
	if ((*env)->input_fd == -1)
		return (err_code(ERROR_FILE, NULL, *env));
	return (1);
}

int		init_output(t_asm *env)
{
	int		fd;

	fd = open(env->name, O_WRONLY | O_CREAT, 0600);
	if (fd == -1)
		return (err_code(ERROR_FILE, NULL, env));
	env->output_fd = fd;
	ft_printf("Writing output program to %s\n", env->name);
	return (1);
}

void	add_to_list(t_asm *env, t_code *n)
{
	t_code	*tmp;

	tmp = env->code;
	while (tmp)
	{
		if (tmp->next == NULL)
		{
			tmp->next = n;
			return ;
		}
		tmp = tmp->next;
	}
	env->code = n;
	return ;
}
