/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 20:40:21 by jvacaris          #+#    #+#             */
/*   Updated: 2022/03/02 20:41:57 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

uint64_t	*set_death_times(int philos, int time2die)
{
	int			a;
	uint64_t	*death_times;

	a = 0;
	death_times = malloc(sizeof(uint64_t) * philos);
	while (a < philos)
	{
		death_times[a] = get_time() + ((uint64_t)time2die * 1000);
		a++;
	}
	return (death_times);
}

void	stop_philos(t_philokit *kit_list)
{
	int	a;

	a = 0;
	while (a < kit_list[0].stats.num_philo)
	{
		pthread_mutex_lock(kit_list[a].comms_mutex);
		if (*(kit_list[a].status) != DEAD)
			*(kit_list[a].status) = STOP;
		pthread_mutex_unlock(kit_list[a].comms_mutex);
		a++;
	}
}
