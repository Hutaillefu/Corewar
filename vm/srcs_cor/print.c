/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/10 14:53:51 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/28 17:42:24 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/corewar.h"

void		print_usage(void)
{
	t_logs *logs;

	logs = ft_memalloc(sizeof(t_logs));
	ft_printf(logs,
	"Usage: ./corewar [-d N -v N -n N] [-a] <champion1.cor> <...>\n");
	ft_printf(logs,
	"%64s\n", "-a        : Prints output from \"aff\" (Default is to hide it)");
	ft_printf(logs, "#### TEXT OUTPUT MODE ###################%s\n",
	"#######################################");
	ft_printf(logs, "%54s\n",
	"-d N      : Dumps memory after N cycles then exits");
	ft_printf(logs, "%73s\n",
	"-v N      : Verbosity levels, can be added together to enable several");
	ft_printf(logs, "%42s\n", "- 0 : Show only essentials");
	ft_printf(logs, "%32s\n", "- 1 : Show lives");
	ft_printf(logs, "%33s\n", "- 2 : Show cycles");
	ft_printf(logs, "%67s\n",
	"- 4 : Show operations (Params are NOT litteral ...)");
	ft_printf(logs, "%33s\n", "- 8 : Show deaths");
	ft_printf(logs, "%59s\n", "- 16 : Show PC movements (Except for jumps)");
	ft_printf(logs, "###########################%s\n",
	"#####################################################");
	dump_logs(logs);
	free(logs);
}

void		ft_print_winner(t_cor *c)
{
	int j;
	int num;

	num = 0;
	j = -1;
	while (++j < c->vm->nb_player)
	{
		if (c->chmp[j]->num == c->vm->chmp_win_num)
			num = j;
	}
	j = -1;
	while (++j < c->vm->nb_player)
	{
		if (c->chmp[j]->num == c->vm->chmp_win_num)
		{
			ft_printf(&(c->vm->logs), "Contestant %d, \"%s\", has won !\n",
			-c->vm->chmp_win_num, c->chmp[num]->name);
			return ;
		}
	}
}

static void	print_map_color(t_cor *c, int i)
{
	t_node		*tmp;
	short int	draw;

	if (c->vm->map_color)
	{
		draw = 0;
		tmp = c->proc->head;
		while (tmp)
		{
			if (tmp->pc == i)
				draw = 1;
			tmp = tmp->next;
		}
		if (!draw)
			ft_printf(&(c->vm->logs), "%3.2x", c->vm->area[i]);
		else
			ft_printf(&(c->vm->logs), "\033[31;01m%3.2x\033[00m",
			c->vm->area[i]);
	}
	else
		ft_printf(&(c->vm->logs), "%3.2x", c->vm->area[i]);
}

void		print_map(t_cor *c, int octet)
{
	int i;
	int j;

	i = -1;
	j = 0;
	ft_printf(&(c->vm->logs), "0x0000 :");
	while (++i < MEM_SIZE)
	{
		if (i != 0 && j == 0)
			ft_printf(&(c->vm->logs), "%#06x :", i);
		++j;
		print_map_color(c, i);
		if (j == octet)
		{
			j = 0;
			ft_printf(&(c->vm->logs), " \n");
		}
	}
}
