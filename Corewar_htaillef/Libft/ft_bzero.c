/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_bzero.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/23 14:11:11 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/11 15:45:11 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char *str;

	str = (unsigned char*)s;
	while (n--)
	{
		*str = '\0';
		str++;
	}
}
