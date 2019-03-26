/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   asm.h                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: quruiz <quruiz@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/18 16:14:38 by quruiz       #+#   ##    ##    #+#       */
/*   Updated: 2019/03/24 01:06:38 by quruiz      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "op.h"
# include "../libft/libft/libft.h"

# define PROG_NAME	env->header->prog_name
# define COMMENT	env->header->comment

/*
**	Error codes
*/

# define MEM_ERROR		1
# define BAD_FILENAME	2
# define ERROR_FILE		3
# define SIZE_ERROR		4
# define SYNTAX_ERROR	5
# define INVALID_OP		6
# define INVALID_PARAM	7
# define NO_TOKEN		8
# define LEXICAL_ERROR	9
# define NEW_LINE		10

/*
**	Structs
*/

typedef struct		s_asm
{
	char			*name;
	int				input_fd;
	int				output_fd;
	int				line_nb;
	struct s_op		*op_tab;
	struct s_header	header;
	struct s_code	*code;
}					t_asm;

typedef struct		s_code
{
	int				type;
	int				line_nb;
	char			*token;
	struct s_op		op;
	unsigned char	byte;
	char			**raw_params;
	intmax_t		params[4];
	int				size;
	struct s_code	*next;
}					t_code;

/*
**	Parsing
*/

int					check_file(t_asm **env, char **arg);
int					read_file(t_asm *env, char **line);
int					get_header(t_asm *env);
int					get_cmd(t_asm *env, char *line);
int					get_label(t_asm *env, char *line);
int					get_op(t_asm *env, char *line);
int					parse_file(t_asm *env);

/*
**	Compilation
*/

int					encode_asm(t_asm *env);
int					handle_reg(t_code *code, int i);
int					handle_direct(t_asm *env, t_code *code, int i);
int					handle_indirect(t_asm *env, t_code *code, int i);
int					init_output(t_asm *env);
int					write_cor(t_asm *env);

/*
**	Tools
*/

void				add_to_list(t_asm *env, t_code *n);

/*
**	Errors and Malloc
*/

void				free_all(t_asm *env);
int					err_code(int code, char *token, t_asm *env);

#endif
