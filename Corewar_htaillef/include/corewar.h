/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   corewar.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/09 14:59:42 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/15 15:45:57 by gzanarel    ###    #+. /#+    ###.fr     */
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

typedef struct		s_vm
{
	int				reg[REG_NUMBER];
	unsigned char	*area;
	int				carry;
	int				nb_player;
	int				cycle_delta;
	int				cycle;
	int				nb_live;
	char			*player[MAX_PLAYERS];
	int				max_chk;
	int				champ_msize;
	unsigned int	prog_size;
}					t_vm;

typedef struct	s_op
{
	char	*name;
	int		nb_params;
	int		param_mask[3];
	int		opcode;
	int		nb_cycles;
	char	*com;
	int		coding_byte;
	int		dir_size;
}				t_op;

typedef struct		s_chmp
{
	unsigned int	magic;
	unsigned int	champ_size;
	char			*name;
	char			*comment;
	char			*infos;
	int				pc;
	int				op_size;
 	struct s_op		op;
	int				param[3][2];
}					t_chmp;


extern	t_op op_tab[17];

typedef struct	s_cor
{
	int				cycle_to_die;
	struct s_vm		*vm;
	struct s_chmp	*chmp[MAX_PLAYERS];
}					t_cor;

/*
** error
*/
void				ft_exit(int error);

/*
** init
*/
void				init_vm(t_cor *c, char **av, int ac);
void				init_map(t_cor *c);
void				init_chmp(t_cor *c);

/*
** print_map
*/
void				print_map(t_cor *c, int octet);

/*
**parse
*/
int					check_parse(t_cor *c, char **av, int ac);
void				check_infos(t_cor *c);

/*
** read_infos
*/
void				read_infos(t_cor *c, char **av);

/*
** cycle
*/
void				cycle(t_cor *c);

int     			exec_process(t_vm *vm, t_chmp *chmp);

void				i_sti(t_chmp *chmp, t_vm *vm);
int   				read_next_uint(t_vm *vm, int index, int bytes_len);
#endif
