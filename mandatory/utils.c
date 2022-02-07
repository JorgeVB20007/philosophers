/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 20:18:37 by jvacaris          #+#    #+#             */
/*   Updated: 2022/02/07 20:42:48 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

long	get_time(void)
{
	struct timeval	time;
	long			total;

	gettimeofday(&time, NULL);
	total = time.tv_usec / 1000 + time.tv_sec * 1000;
	return (total);
}

int	positive_atoi(char *str)
{
	int	a;
	int	status;

	a = -1;
	status = 1;
	while (str[++a])
	{
		if (str[a] < '0' || str[a] > '9')
			status = 0;
	}
	if (status)
		return (ft_atoi(str));
	else
		return (-1);
}
