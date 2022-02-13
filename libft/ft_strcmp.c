/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 19:26:24 by jvacaris          #+#    #+#             */
/*   Updated: 2022/02/13 18:53:21 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	a;

	a = 0;
	if (!s1 && !s2)
		return (0);
	else if (s1 && !s2)
		return (s1[a]);
	else if (!s1 && s2)
		return (-s2[a]);
	while (s1[a] && s2[a])
	{
		if (s1[a] != s2[a])
		{
			return (s1[a] - s2[a]);
		}
		a++;
	}
	return (s1[a] - s2[a]);
}
