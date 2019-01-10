/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/09 15:04:49 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/10 17:45:20 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/corewar.h"

void ft_exit(void)
{
	printf("Error parsing ac < 2 || ac > 5 | error open == -1\n");
	exit(1);
}

int     check_parse(t_cor *c, char **av, int ac)
{
	int i;
	int fd;
	char *tmp;

	i = 1;
	if (ac < 2 || ac > MAX_ARGS_NUMBER + 1)
		ft_exit();
	//if option -flag rajouter ici
	while (av[i])
	{
		printf("i: %d\n", i);
		printf("player: %d\n", c->vm->nb_player);
		tmp = ft_strsub(av[i], (ft_strlen(av[i]) - 4), ft_strlen(av[i]));
		if ((ft_strcmp(".cor", tmp)))
			ft_exit();
		if (c->vm->nb_player < 4)
			c->vm->player[c->vm->nb_player++] = ft_strdup(av[i]);
		if (i < ac)
			i++;
		else
			break ;
	}
	return (0);
}

void	cycle(t_cor *c)
{
	int cycle;

	// printf("c->cycle_to_die: %d\n", c->cycle_to_die);
	while (c->cycle_to_die > 0)
	{
		// printf("C: %d\n", c->vm->cycle);
		// printf("CtD: %d\n", c->cycle_to_die);
		cycle = 0;
		while (++cycle <= c->cycle_to_die)
		{
			//exec processus
			c->vm->cycle++;
			if (cycle == c->cycle_to_die)
				c->cycle_to_die -= c->vm->cycle_delta;
		}
	}
}

void	champ_info(t_cor *c)
{
}

int		main(int ac, char **av)
{
	t_cor *c;
	char *line;

	c = ft_memalloc(sizeof(t_cor));
	init_vm(c);
	// if (check_parse(c, av, ac) == 1)
	// 	ft_exit();
	// champ_info(&c);
	int fd = open(av[1], O_RDONLY);
	off_t off = lseek(fd, 0, SEEK_END);
	printf("off: %lld\n", off);
	close(fd);
	fd = open(av[1], O_RDONLY);
	line = ft_memalloc(off);
	read(fd, line, off);
	// for (int i = 0; i < off; i++)
		// printf("%c", line[i]);
	// char *tmp = ft_strsub(line, 2176, off - 2176);
	// printf("tmp: %x\n", tmp);
	// printf("len: %zu\n", strlen(line));
	// printf("len: %#x\n", line);
	c->vm->area = memcpy(c->vm->area, line, off);
	print_map(c);

	printf("%s\n", extract_prog_name(c->vm, 0)); // 0 for first champ
	printf("%s\n", extract_prog_comment(c->vm, 0)); // 0 for first champ
	
	//printf("%s\n", c->vm->area);
	cycle(c);
	return (0);
}
