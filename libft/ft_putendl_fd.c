/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 19:19:39 by jvacaris          #+#    #+#             */
/*   Updated: 2021/06/04 19:19:42 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	int	a;

	a = 0;
	if (!s)
		return ;
	while (s[a] != 0)
	{
		write(fd, &s[a], 1);
		a++;
	}
	write(fd, "\n", 1);
}