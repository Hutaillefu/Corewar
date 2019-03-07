/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/15 13:31:55 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/07 16:53:17 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/corewar.h"

static void	check_verb(t_vm *vm, char *av)
{
	if (!av)
		ft_exit(5, av);
	vm->verbose = ft_atoi(av);
	if (vm->verbose < 0 || vm->verbose > 31)
		vm->verbose = 0;
}

static void	check_num(t_vm *vm, char *av)
{
	int j;

	j = -1;
	if (!av)
		ft_exit(5, av);
	while (av[++j])
		if (ft_isalnum(av[j]) == 0)
			ft_exit(5, av);
	vm->num[vm->nb_player] = ft_atoi(av);
}

static void	check_dump(t_vm *vm, char *av)
{
	int j;

	j = -1;
	if (!av)
		ft_exit(5, av);
	while (av[++j])
		if (ft_isalnum(av[j]) == 0)
			ft_exit(5, av);
	vm->dump = ft_atoi(av);
}

int     check_parse(t_vm *vm, char **av, int ac)
{
	int i;
	char *tmp;
	int len;

	i = 1;
	if (ac < 2)
		ft_exit(0, av[i]);
	while (i < ac)
	{
		len = 0;
		if (!ft_strcmp(av[i], "-d"))
			check_dump(vm, av[++i]);
		else if (!ft_strcmp(av[i], "-n"))
			check_num(vm, av[++i]);
		else if (!ft_strcmp(av[i], "-v"))
			check_verb(vm, av[++i]);
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
