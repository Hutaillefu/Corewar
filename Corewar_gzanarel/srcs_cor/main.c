/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/09 15:04:49 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/22 16:26:40 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/corewar.h"

static void	print_usage(void)
{
	t_logs *logs;

	printf("len: %lu\n", strlen("-a        : Prints output from \"aff\" (Default is to hide it)"));
	logs = ft_memalloc(sizeof(t_logs));
	ft_printf(logs, "Usage: ./corewar [-d N -s N -v N | -b --stealth | -n --stealth] [-a] <champion1.cor> <...>\n");
    ft_printf(logs, "%64s\n", "-a        : Prints output from \"aff\" (Default is to hide it)");
// 	#### TEXT OUTPUT MODE ##########################################################\n
//     -d N      : Dumps memory after N cycles then exits\n
//     -s N      : Runs N cycles, dumps memory, pauses, then repeats\n
//     -v N      : Verbosity levels, can be added together to enable several
//                 - 0 : Show only essentials
//                 - 1 : Show lives
//                 - 2 : Show cycles
//                 - 4 : Show operations (Params are NOT litteral ...)
//                 - 8 : Show deaths
//                 - 16 : Show PC movements (Except for jumps)
// #### BINARY OUTPUT MODE ########################################################
//     -b        : Binary output mode for corewar.42.fr
//     --stealth : Hides the real contents of the memory
// #### NCURSES OUTPUT MODE #######################################################
//     -n        : Ncurses output mode
//     --stealth : Hides the real contents of the memory
// ################################################################################
// }

// Usage: ./corewar [-d N -s N -v N | -b --stealth | -n --stealth] [-a] <champion1.cor> <...>
//     -a        : Prints output from "aff" (Default is to hide it)
// #### TEXT OUTPUT MODE ##########################################################
//     -d N      : Dumps memory after N cycles then exits
//     -s N      : Runs N cycles, dumps memory, pauses, then repeats
//     -v N      : Verbosity levels, can be added together to enable several
//                 - 0 : Show only essentials
//                 - 1 : Show lives
//                 - 2 : Show cycles
//                 - 4 : Show operations (Params are NOT litteral ...)
//                 - 8 : Show deaths
//                 - 16 : Show PC movements (Except for jumps)
// #### BINARY OUTPUT MODE ########################################################
//     -b        : Binary output mode for corewar.42.fr
//     --stealth : Hides the real contents of the memory
// #### NCURSES OUTPUT MODE #######################################################
//     -n        : Ncurses output mode
//     --stealth : Hides the real contents of the memory
// ################################################################################
dump_logs(logs);
exit(0);
}

int			main(int ac, char **av)
{
	t_cor *c;

	if (ac < 2)
		print_usage();
	c = init_cor(av, ac);
	read_infos(c);
	init_map(c);
	cycle(c);
	ft_print_winner(c);
	dump_logs(&(c->vm->logs));
	return (0);
}
