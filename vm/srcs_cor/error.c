/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   error.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/15 13:37:01 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/26 19:10:22 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/corewar.h"

void	del_list(t_list2 *l)
{
	t_node *current;
	t_node *next;

	current = l->head;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	l->head = NULL;
	l->tail = NULL;
	free(l);
}

void	free_vm(t_vm **vm)
{
	int i;

	if (!vm || !(*vm))
		return ;
	(*vm)->area ? free((*vm)->area) : 0;
	i = -1;
	while (++i < (*vm)->nb_player)
		free((*vm)->player[i]);
	free(*vm);
	*vm = NULL;
}

void	free_cor(t_cor **c)
{
	int i;

	if (!c || !(*c))
		return ;
	i = -1;
	while (++i < (*c)->vm->nb_player)
	{
		if ((*c)->chmp[i])
		{
			(*c)->chmp[i]->name ? free((*c)->chmp[i]->name) : 0;
			(*c)->chmp[i]->comment ? free((*c)->chmp[i]->comment) : 0;
			(*c)->chmp[i]->infos ? free((*c)->chmp[i]->infos) : 0;
			(*c)->chmp[i] ? free((*c)->chmp[i]) : 0;
		}
	}
	free_vm(&(*c)->vm);
	del_list((*c)->proc);
	free(*c);
	*c = NULL;
}

void	ft_exit(t_logs *logs, int error, char *s, t_cor *c)
{
	if (error == 0)
		ft_printf(logs,
		"Usage: ./corewar [-d N -v | -n N] <champion1.cor> <...>\n");
	if (error == 1)
		ft_printf(logs, "Error parsing ac < 2 or open == -1\n");
	if (error == 2)
		ft_printf(logs, "Error not files '.cor'\n");
	if (error == 3)
		ft_printf(logs, "Error: %s has too large a code (> 682 bytes)\n", s);
	if (error == 5)
		ft_printf(logs,
		"Error: Flag -d doit etre suivi d'une valeur positive\n");
	if (error == 6)
		ft_printf(logs, "Too many champions\n");
	if (error == 7)
		ft_printf(logs, "Can't read source file %s\n", s);
	if (error == 8)
		ft_printf(logs, "Error malloc\n");
	if (error == 9)
		ft_printf(logs, "Error: File chmps is too small to be a champion\n");
	dump_logs(logs);
	free_cor(&c);
	exit(1);
}
