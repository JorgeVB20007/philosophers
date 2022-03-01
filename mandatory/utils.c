/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 18:14:33 by jvacaris          #+#    #+#             */
/*   Updated: 2022/03/02 00:29:16 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	printer(t_philokit kit, char *action)
{
	if (check_int_with_mutex(kit.status, kit.comms_mutex) != STOP)
	{
		pthread_mutex_lock(kit.stats.printer_key);
		if (check_int_with_mutex(kit.status, kit.comms_mutex) != STOP)
		{
			if ((check_int_with_mutex(kit.status, kit.comms_mutex) == DEAD && !ft_strcmp(action, DIE)) || check_int_with_mutex(kit.status, kit.comms_mutex) != DEAD)
			{
				if (check_int_with_mutex(kit.status, kit.comms_mutex) == DEAD)
				{
					pthread_mutex_lock(kit.comms_mutex);
					printf("%6llu %s%3d%s %s\n", (get_time() - *(kit.stats.start_time)) / 1000, BOLD, kit.id, FMT_RST, action);
					*(kit.status) = STOP;
					pthread_mutex_unlock(kit.comms_mutex);
				}
				else
				{
					pthread_mutex_lock(kit.comms_mutex);
					printf("%6llu %s%3d%s %s\n", (get_time() - *(kit.stats.start_time)) / 1000, BOLD, kit.id, FMT_RST, action);
					pthread_mutex_unlock(kit.comms_mutex);
				}
			}
		}
		pthread_mutex_unlock(kit.stats.printer_key);
	}
}

// Will wait *time* microseconds.
void	ft_wait(int time, uint64_t delay)
{
	struct		timeval		act_time;
	uint64_t	final_time;
	uint64_t	current_time;

	gettimeofday(&act_time, NULL);
	current_time = act_time.tv_usec + act_time.tv_sec * 1000000;
	final_time = (current_time + (uint64_t)time * 1000) - delay;
	while (final_time > current_time)
	{
		usleep ((final_time - current_time) / 2);
		gettimeofday(&act_time, NULL);
		current_time = act_time.tv_usec + act_time.tv_sec * 1000000;
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
uint64_t	get_time()
{
	struct timeval		time;
	uint64_t	total;

	gettimeofday(&time, NULL);
	total = time.tv_usec + time.tv_sec * 1000000;
	return (total);
}

int	change_if_possible(t_philokit kit, int action, pthread_mutex_t *comms_mutex)
{
	int	returning;

	returning = 0;
	pthread_mutex_lock(comms_mutex);
	if (*(kit.status) == DEAD || *(kit.status) == STOP)
		returning = *(kit.status);
	else
		returning = action;
	pthread_mutex_unlock(comms_mutex);
	return (returning);
}

int	check_int_with_mutex(int *number, pthread_mutex_t *comms_mutex)
{
	int	returning;

	returning = 0;
	pthread_mutex_lock(comms_mutex);
	returning = *number;
	pthread_mutex_unlock(comms_mutex);
	return (returning);
}

uint64_t	check_uint64t_with_mutex(uint64_t *number, pthread_mutex_t *comms_mutex)
{
	uint64_t	returning;

	returning = 0;
	pthread_mutex_lock(comms_mutex);
	returning = *number;
	pthread_mutex_unlock(comms_mutex);
	return(returning);
}
