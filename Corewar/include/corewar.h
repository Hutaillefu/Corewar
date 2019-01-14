/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   corewar.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/09 14:59:42 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/10 17:43:53 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "op.h"
# include "../Libft/includes/libft.h"

typedef struct		s_line
{
	char			*line;
	int				size;
}					t_line;

typedef struct	s_vm
{
	int			*pc;
	int			reg[REG_NUMBER][REG_SIZE];
	unsigned char		*area;
	int			carry;
	int			nb_player;
	int			cycle_delta;
	int			cycle;
	int			nb_live;
	char		*player[MAX_ARGS_NUMBER];
	int			max_chk;
	int			champ_msize;
}				t_vm;

typedef struct	s_cor
{
	int			cycle_to_die;
	struct s_vm		*vm;
}				t_cor;






void	ft_exit(void);
void	init_vm(t_cor *c);
void	print_map(t_cor *c);

char    *extract_prog_name(t_vm *vm);
char    *extract_prog_comment(t_vm *vm);
unsigned int extract_prog_size(t_vm *vm);
#endif
