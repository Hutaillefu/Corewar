/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_logs.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: htaillef <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/27 15:09:38 by htaillef     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/27 15:09:40 by htaillef    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

int		init_logs(t_logs *logs)
{
	int	i;

	if (!logs || logs->buffer)
		return (0);
	if (!(logs->buffer = (char *)malloc(sizeof(char) * LOGS_LEN + 1)))
		return (0);
	i = -1;
	while (++i < LOGS_LEN + 1)
		logs->buffer[i] = '\0';
	return (1);
}

void	dump_logs(t_logs *logs)
{
	if (!logs || !(logs->buffer))
		return ;
	write(1, logs->buffer, ft_strlen(logs->buffer));
	ft_memdel((void **)&(logs->buffer));
	logs->len = 0;
}

void	add_logs(t_logs *logs, char *log)
{
	size_t	i;

	if (!logs || !(logs->buffer) || !log)
		return ;
	if (ft_strlen(log) + logs->len > LOGS_LEN)
	{
		dump_logs(logs);
		init_logs(logs);
	}
	i = -1;
	while (++i < ft_strlen(log))
	{
		logs->buffer[logs->len] = log[i];
		logs->len++;
	}
	logs->buffer[logs->len] = '\0';
}
