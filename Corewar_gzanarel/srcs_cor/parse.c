/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/15 13:31:55 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/22 19:14:24 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/corewar.h"

static void	check_verb(t_cor *c, t_vm *vm, char *av)
{
	if (!av)
		ft_exit(&(vm->logs), 5, av, c);
	vm->verbose = ft_atoi(av);
	if (vm->verbose < 0 || vm->verbose > 31)
		vm->verbose = 0;
}

static void	check_num(t_cor *c, t_vm *vm, char *av)
{
	int j;

	j = -1;
	if (!av)
		ft_exit(&(vm->logs), 5, av, c);
	while (av[++j])
		if (ft_isalnum(av[j]) == 0)
			ft_exit(&(vm->logs), 5, av, c);
	vm->num[vm->nb_player] = ft_atoi(av);
}

static void	check_dump(t_cor *c, t_vm *vm, char *av)
{
	int j;

	j = -1;
	if (!av)
		ft_exit(&(vm->logs), 5, av, c);
	while (av[++j])
		if (ft_isalnum(av[j]) == 0)
			ft_exit(&(vm->logs), 5, av, c);
	vm->dump = ft_atoi(av);
}

static int	check_files(t_cor *c, t_vm *vm, char *av, int len)
{
	char *tmp;

	if (open(av, 1) < 0)
		ft_exit(&(vm->logs), 7, av, c);
	tmp = ft_strsub(av, (len - 4), len);
	if (ft_strcmp(".cor", tmp))
		ft_exit(&(vm->logs), 2, av, c);
	else if (vm->nb_player < MAX_PLAYERS)
		vm->player[vm->nb_player++] = ft_strdup(av);
	else if (vm->nb_player >= MAX_PLAYERS)
		ft_exit(&(vm->logs), 6, av, c);
	free(tmp);
	return (1);
}

int			check_parse(t_cor *c, t_vm *vm, char **av, int ac)
{
	int i;
	int len;

	i = 0;
	while (++i < ac)
	{
		len = 0;
		if (!ft_strcmp(av[i], "-d"))
			check_dump(c, vm, av[++i]);
		else if (!ft_strcmp(av[i], "-n"))
			check_num(c, vm, av[++i]);
		else if (!ft_strcmp(av[i], "-v"))
			check_verb(c, vm, av[++i]);
		else if (!ft_strcmp(av[i], "-a"))
			vm->aff = 1;
		else if ((len = ft_strlen(av[i])) > 4)
			check_files(c, vm, av[i], len);
		else
			ft_exit(&(vm->logs), 8, av[i], c);
	}
	if (vm->nb_player == 0)
		ft_exit(&(vm->logs), 5, av[i], c);
	return (0);
}
