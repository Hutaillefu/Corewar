/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   corewar.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/09 14:59:42 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/08 13:15:18 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "op.h"
# include "../Libft/includes/libft.h"

# define V_LIVE 1
# define V_CYCLE 2
# define V_OP 4
# define V_DEATH 8
# define V_ADV 16

typedef struct		s_line
{
	char			*line;
	int				size;
}					t_line;

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

typedef struct s_node
{
	int				carry;
	int				pc;
	int				pc_b;
	int				op_size;
	struct s_op		op;
	int				exec;
	int				param[3][2];
	int				reg[REG_NUMBER];
	int				last_live;
	int				lives;
	int				num;
	struct s_node	*next;
	struct s_node	*prev;
}				t_node;

typedef struct s_list2
{
	t_node *head;
	t_node *tail;
	int 	len;
}				t_list2;

typedef struct		s_chmp
{
	unsigned int	magic;
	unsigned int	champ_size;
	char			*name;
	char			*comment;
	char			*infos;
	int				last_live;
	int				num;
}					t_chmp;

typedef struct		s_vm
{
	unsigned char	*area;
	int				nb_player;
	int				cycle_delta;
	int				cycle;
	int				nb_live;
	char			*player[MAX_PLAYERS];
	int				max_chk;
	int				champ_msize;
	unsigned int	prog_size;
	int				dump;
	int				aff;
	int				chmp_win_num;
	int				cycle_to_die;
	int				num[MAX_PLAYERS];
	char				verbose;
}					t_vm;

extern	t_op op_tab[17];

typedef struct	s_cor
{
	struct s_vm		*vm;
	struct s_chmp	*chmp[MAX_PLAYERS];
	struct s_list2	*proc;
}					t_cor;

/*
** list
*/
void			add_element_end(t_list2 **lst, t_cor *c, t_chmp *chmp, int i);
t_node			*clone_proc(t_node *parent);
void			push_back(t_list2 **lst, t_node *proc);
void			push_front(t_list2 **lst, t_node *proc);


/*
** error
*/
void				ft_exit(int error, char *s);

/*
** init
*/
t_cor	*init_cor(char **av, int ac);
void				init_vm(t_vm *vm);
void				init_map(t_cor *c);
void				init_proc(t_cor *c, t_list2 *proc);
void				init_num_chmp(t_cor *c, int i);

/*
** print
*/
void				print_map(t_cor *c, int octet);
void		ft_print_winner(t_cor *c);

/*
**parse
*/
int					check_parse(t_vm *vm, char **av, int ac);

/*
** read_infos
*/
void		read_infos(t_cor *c);
int	little_endian(int value);
int    read_next_uint(t_vm *vm, int index, int bytes_len);


/*
** cycle
*/
void				cycle(t_cor *c);

int     exec_process(t_vm *vm, t_node *proc);
int		load(t_vm *vm, t_node *proc);
int		exec(t_vm *vm, t_node *proc);
int     check_processus(t_vm *vm, t_node *proc);
/*
** processus
*/
int		start_processus(t_cor *cor, t_node *proc);
void	load_processus(int start, t_node *proc);

/*
** flags
*/
void	ft_flag_dump(t_cor *c);


/*
** commande
*/
void	i_lfork(t_node *proc, t_cor *cor);
void	i_sti(t_node *proc, t_vm *vm);
void	i_fork(t_node *proc, t_cor *cor);
void	i_lld(t_node *proc, t_vm *vm);
void	i_ld(t_node *proc, t_vm *vm);
void	i_add(t_node *proc, t_vm *vm);
void	i_zjmp(t_node *proc, t_vm *vm);
void	i_sub(t_node *proc, t_vm *vm);
void	i_ldi(t_node *proc, t_vm *vm);
void	i_or(t_node *proc, t_vm *vm);
void	i_st(t_node *proc, t_vm *vm);
void	i_aff(t_node *proc, t_vm *vm);
void	i_live(t_node *proc, t_cor *cor);
void	i_xor(t_node *proc, t_vm *vm);
void	i_lldi(t_node *proc, t_vm *vm);
void	i_and(t_node *proc, t_vm *vm);

// <br>* Champion sans nom / sans commentaire
// <br>* Champion avec un nom ou un commentaire trop long
// <br>* Champion sans code
// <br>
// <br>De nombreuses façons de gérer ces erreurs sont acceptables, comme par exemple :
// <br>* Refuser de compiler le champion
// <br>* Refuser de lancer le champion
// <br>* Corriger automatiquement le champion
// <br>* Lancer le champion même s'il n'a a


#endif
