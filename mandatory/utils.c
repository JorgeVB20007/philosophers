/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 18:14:33 by jvacaris          #+#    #+#             */
/*   Updated: 2022/02/15 19:05:54 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	printer(t_philokit kit, char *action)
{
	pthread_mutex_lock(kit.stats.printer_key);
	printf("%6llu %s%d%s %s\n", get_time() - kit.stats.start_time, BOLD, kit.id, FMT_RST, action);
	pthread_mutex_unlock(kit.stats.printer_key);
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
