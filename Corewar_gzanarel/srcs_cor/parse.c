/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/15 13:31:55 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/07 13:41:59 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/corewar.h"

int		check_num(t_vm *vm, char **av, int i)
{
	int j;

	j = -1;
	if (!av[i])
		ft_exit(5, av[i]);
	while (av[i][++j])
		if (ft_isalnum(av[i][j]) == 0)
			ft_exit(5, av[i]);
	vm->num[vm->nb_player] = ft_atoi(av[i]);
	return (1);
}

int		check_dump(t_vm *vm, char **av, int i)
{
	int j;

	j = -1;
	if (!av[i])
		ft_exit(5, av[i]);
	while (av[i][++j])
		if (ft_isalnum(av[i][j]) == 0)
			ft_exit(5, av[i]);
	vm->dump = ft_atoi(av[i]);
	return (1);
}

int     check_parse(t_vm *vm, char **av, int ac)
{
	int i;
	char *tmp;
	int len;

	i = 1;
	if (ac < 2)
		ft_exit(0, av[i]);
	while (av[i])
	{
		len = 0;
		if (!ft_strcmp(av[i], "-d"))
			i += check_dump(vm, av, i + 1);
		else if (!ft_strcmp(av[i], "-n"))
			i += check_num(vm, av, i + 1);
		else if (!ft_strcmp(av[i], "-v"))
			vm->verbose = 1;
			// i += ft_verbose(vm, av[i + 1]);
		else if ((len = ft_strlen(av[i])) > 4)
		{
			if (open(av[i], 1) < 0)
				ft_exit(7, av[i]);
			tmp = ft_strsub(av[i], (len - 4), len);
			if (ft_strcmp(".cor", tmp))
				ft_exit(2, av[i]);
			else if (vm->nb_player < MAX_PLAYERS)
				vm->player[vm->nb_player++] = ft_strdup(av[i]);
			else if (vm->nb_player >= MAX_PLAYERS)
				ft_exit(6, av[i]);
		}
		else
			ft_exit(2, av[i]);
		if (i < ac)
			i++;
		else
			break ;
	}
	if (vm->nb_player == 0)
		ft_exit(5, av[i]);
	return (0);
}
