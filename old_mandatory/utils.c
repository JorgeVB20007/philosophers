/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 20:18:37 by jvacaris          #+#    #+#             */
/*   Updated: 2022/02/14 22:17:10 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/*
* Gets the time in miliseconds (ms)
? 1000usec = 1msec | 1000msec = 1sec
*/
/*unsigned long long	get_time(t_philokit kit)
{
	struct timeval	time;
	unsigned long long			total;

	pthread_mutex_lock(kit.input.time_key);
	gettimeofday(&time, NULL);
	total = time.tv_usec / 1000 + time.tv_sec * 1000;
	pthread_mutex_unlock(kit.input.time_key);
	return (total);
}

unsigned long long	get_time2(void)
{
	struct timeval	time;
	unsigned long long			total;

	gettimeofday(&time, NULL);
	total = time.tv_usec / 1000 + time.tv_sec * 1000;
	return (total);
}*/

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

/*
*	Returns 1 if someone died or everyone ate 6 times. Returns 0 otherwise.
*/
int	is_ok_to_end(t_philokit kit)
{
	if (*(kit.someone_died) < 0 || *(kit.someone_died) >= kit.input.num_philo)
		return (1);
	else
		return (0);
}
