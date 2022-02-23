/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 18:14:33 by jvacaris          #+#    #+#             */
/*   Updated: 2022/02/23 22:58:55 by jvacaris         ###   ########.fr       */
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
			printf("%d   %6llu %s%3d%s %s\n", (*(kit.status) == DEAD * 2) + (*(kit.status) == STOP), get_time() - kit.stats.start_time, BOLD, kit.id, FMT_RST, action);
		}
		if (*(kit.status) == DEAD)
		{
			*(kit.status) = STOP;
			ft_wait(50);
		}
		pthread_mutex_unlock(kit.stats.printer_key);
	}
}

// Will wait *time* nanoseconds.
void	ft_wait(int time)
{
	unsigned long long	final_time;

	final_time = get_time() + (unsigned long long) time;
	while (final_time > get_time())
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

unsigned long long	get_time(void)
{
	struct timeval		time;
	unsigned long long	total;

	gettimeofday(&time, NULL);
	total = time.tv_usec / 1000 + time.tv_sec * 1000;
	return (total);
}

int	change_if_possible(t_philokit kit, int action)
{
	if (*(kit.status) == DEAD || *(kit.status) == STOP)
		return (*(kit.status));
	else
		return (action);
}
