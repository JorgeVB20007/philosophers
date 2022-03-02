/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_creators.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 20:39:37 by jvacaris          #+#    #+#             */
/*   Updated: 2022/03/02 20:39:40 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

pthread_mutex_t	*create_comms_mutex(t_stats stats)
{
	int				ctr;
	pthread_mutex_t	*mutex_list;

	ctr = -1;
	mutex_list = malloc(sizeof(pthread_mutex_t) * stats.num_philo);
	while (++ctr < stats.num_philo)
	{
		pthread_mutex_init(&(mutex_list[ctr]), NULL);
	}
	return (mutex_list);
}

pthread_mutex_t	*create_forks(t_stats stats)
{
	int				ctr;
	pthread_mutex_t	*mutex_list;

	ctr = -1;
	mutex_list = malloc(sizeof(pthread_mutex_t) * stats.num_philo);
	while (++ctr < stats.num_philo)
	{
		pthread_mutex_init(&(mutex_list[ctr]), NULL);
	}
	return (mutex_list);
}

void	destroy_forks(t_stats stats, pthread_mutex_t *fork_list, \
pthread_mutex_t *eats_list)
{
	int				ctr;

	ctr = -1;
	while (++ctr < stats.num_philo)
	{
		pthread_mutex_destroy(&(fork_list[ctr]));
		pthread_mutex_destroy(&(eats_list[ctr]));
	}
	free(fork_list);
	free(eats_list);
	return ;
}

t_philokit	*create_kits(t_stats stats, pthread_mutex_t *forks, \
pthread_mutex_t *comms_mutex_list)
{
	t_philokit	*kit_list;
	int			ctr;

	ctr = -1;
	kit_list = malloc(sizeof(t_philokit) * stats.num_philo);
	while (++ctr < stats.num_philo)
	{
		kit_list[ctr].id = ctr + 1;
		kit_list[ctr].temp_status = THINKING;
		kit_list[ctr].status = &(kit_list[ctr].temp_status);
		kit_list[ctr].times_eaten = 0;
		kit_list[ctr].stats = stats;
		kit_list[ctr].temp_just_ate = 0;
		kit_list[ctr].just_ate = &(kit_list[ctr].temp_just_ate);
		kit_list[ctr].comms_mutex = &(comms_mutex_list[ctr]);
		kit_list[ctr].left = &(forks[ctr]);
		if (ctr == 0)
			kit_list[ctr].right = &(forks[stats.num_philo - 1]);
		else
			kit_list[ctr].right = &(forks[ctr - 1]);
	}
	return (kit_list);
}
