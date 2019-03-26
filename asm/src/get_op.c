/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_op.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: quruiz <quruiz@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/31 20:59:46 by quruiz       #+#   ##    ##    #+#       */
/*   Updated: 2019/03/21 20:48:14 by quruiz      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/asm.h"

extern t_op	g_op_tab[17];

void		save_size_param(char type, t_code *code, int i)
{
	if (type == T_REG)
	{
		code->byte = code->byte | (REG_CODE << (6 - (i * 2)));
		code->size += 1;
	}
	else if (type == T_DIR)
	{
		code->byte = code->byte | (DIR_CODE << (6 - (i * 2)));
		code->size += (code->op.dir_size ? 2 : 4);
	}
	else if (type == T_IND)
	{
		code->byte = code->byte | (IND_CODE << (6 - (i * 2)));
		code->size += 2;
	}
}

t_code		*create_struct_op(t_asm *env, t_code *tmp)
{
	t_code	*n;
	int		i;

	i = 0;
	if (!(n = ft_memalloc(sizeof(t_code))))
		return (err_code(MEM_ERROR, NULL, env) ? 0 : NULL);
	n->type = 2;
	n->line_nb = env->line_nb;
	n->token = ft_strdup(tmp->op.name);
	n->op = tmp->op;
	n->byte = tmp->byte;
	n->raw_params = tmp->raw_params;
	n->size = tmp->size;
	n->next = NULL;
	return (n);
}

t_code		*detect_param(t_asm *env, char **param, int op)
{
	int		i;
	t_code	tmp;

	i = 0;
	tmp.size = (g_op_tab[op].byte_param) + 1;
	tmp.op = g_op_tab[op];
	tmp.byte = 0;
	while (i < g_op_tab[op].nb_param)
	{
		if (param[i][0] == 'r' && (g_op_tab[op].arg[i] & T_REG))
			save_size_param(T_REG, &tmp, i);
		else if (param[i][0] == DIRECT_CHAR && (g_op_tab[op].arg[i] & T_DIR))
			save_size_param(T_DIR, &tmp, i);
		else if ((ft_str_is_numeric(param[i]) || param[i][0] == LABEL_CHAR) &&
			(g_op_tab[op].arg[i] & T_IND))
			save_size_param(T_IND, &tmp, i);
		else
			return (err_code(INVALID_PARAM, g_op_tab[op].name, env) ? 0 : NULL);
		i++;
	}
	tmp.raw_params = param;
	return (create_struct_op(env, &tmp));
}

int			parse_op(t_asm *env, char *line, int cursor, int op_code)
{
	char	**param;
	t_code	*code;
	int		i;

	i = 0;
	if (ft_str_is_empty(line + cursor))
		return (err_code(SYNTAX_ERROR, g_op_tab[op_code].name, env));
	param = ft_strsplit_trim(line + cursor, SEPARATOR_CHAR);
	while (i < g_op_tab[op_code].nb_param && param[i] &&
		!ft_str_is_empty(param[i]))
		i++;
	if (i != g_op_tab[op_code].nb_param)
	{
		ft_freesplit(param);
		return (err_code(INVALID_PARAM, g_op_tab[op_code].name, env));
	}
	if (!(code = detect_param(env, param, op_code)))
		return (ft_freesplit(param));
	add_to_list(env, code);
	return (1);
}

int			get_op(t_asm *env, char *line)
{
	char	*op;
	int		cursor;
	int		op_code;

	cursor = 0;
	op_code = 0;
	while (ft_isalpha(line[cursor]))
		cursor++;
	if (!cursor)
		return (err_code(LEXICAL_ERROR, NULL, env));
	op = ft_strsub(line, 0, cursor);
	while (op_code < 16)
	{
		if (ft_strequ(op, g_op_tab[op_code].name))
			break ;
		op_code++;
	}
	ft_strdel(&op);
	if (op_code == 16)
		return (err_code(INVALID_OP, NULL, env));
	if (!parse_op(env, line, cursor, op_code))
		return (0);
	return (1);
}
