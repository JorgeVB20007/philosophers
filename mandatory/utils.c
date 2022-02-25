/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 18:14:33 by jvacaris          #+#    #+#             */
/*   Updated: 2022/02/25 23:18:31 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	printer(t_philokit kit, char *action)
{
	if (*(kit.status) != STOP)
	{
		pthread_mutex_lock(kit.stats.printer_key);
		if (*(kit.status) != STOP)
		{
			if ((*(kit.status) == DEAD && !ft_strcmp(action, DIE)) || *(kit.status) != DEAD)
			{
				if (*(kit.status) == DEAD)
				{
					ft_wait(1, kit.stats.timer_key);
					printf("%d  %6llu %s%3d%s %s\n", (*(kit.status) == DEAD) + (*(kit.status) == STOP) * 2, (get_time(kit.stats.timer_key) - kit.stats.start_time) / 1/*000*/, BOLD, kit.id, FMT_RST, action);
					*(kit.status) = STOP;
				}
				else
					printf("%d  %6llu %s%3d%s %s\n", (*(kit.status) == DEAD) + (*(kit.status) == STOP) * 2, (get_time(kit.stats.timer_key) - kit.stats.start_time) / 1/*000*/, BOLD, kit.id, FMT_RST, action);
			}
		}
//		ft_wait(2, kit.stats.timer_key);
		pthread_mutex_unlock(kit.stats.printer_key);
	}
}

// Will wait *time* microseconds.
void	ft_wait(int time, pthread_mutex_t *timer_key)
{
	unsigned long long	final_time;

	final_time = get_time(timer_key) + (unsigned long long)time * 1000;
	while (final_time > get_time(timer_key))
	{
		usleep (5);
	}
}

int	positive_atoi(char *str)
{
	int	a;
	int	status;

	a = -1;
	status = 1;
	if (str[0] == '+')
		a++;
	if (!str[a + 1])
		status = 0;
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

// Gets the time in microseconds.
unsigned long long	get_time(pthread_mutex_t *timer_key)
{
	struct timeval		time;
	unsigned long long	total;

	pthread_mutex_lock(timer_key);
	gettimeofday(&time, NULL);
	pthread_mutex_unlock(timer_key);
	total = time.tv_usec + time.tv_sec * 1000000;
	return (total);
}

int	change_if_possible(t_philokit kit, int action)
{
	pthread_mutex_lock(kit.stats.timer_key);
	if (*(kit.status) == DEAD || *(kit.status) == STOP)
		return (*(kit.status));
	else
		return (action);
}
