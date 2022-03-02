/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 18:14:20 by jvacaris          #+#    #+#             */
/*   Updated: 2022/03/02 21:15:43 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	control_tower_check4end(t_philokit *kit_list, \
uint64_t *death_times, int *ctr, int end_eats)
{
	uint64_t	time;

	time = get_time();
	if (death_times[*ctr] < time)
	{
		pthread_mutex_lock(kit_list[0].stats.timer_key);
		stop_philos(kit_list);
		pthread_mutex_lock(kit_list[*ctr].comms_mutex);
		*(kit_list[*ctr].status) = DEAD;
		pthread_mutex_unlock(kit_list[*ctr].comms_mutex);
		pthread_mutex_unlock(kit_list[0].stats.timer_key);
		printer((kit_list[*ctr]), DIE);
		*ctr = -2;
		return (1);
	}
	if (end_eats >= kit_list[0].stats.num_philo)
	{
		pthread_mutex_lock(kit_list[0].stats.timer_key);
		stop_philos(kit_list);
		pthread_mutex_unlock(kit_list[0].stats.timer_key);
		return (1);
	}
	return (0);
}

static int	control_tower_routine(t_philokit *kit_list, t_stats stats, \
uint64_t *death_times, int *end_eats)
{
	int			ctr;
	uint64_t	time;

	ctr = -1;
	while (++ctr < stats.num_philo)
	{
		time = get_time();
		pthread_mutex_lock(kit_list[ctr].comms_mutex);
		if (*(kit_list[ctr].just_ate) > 0)
		{
			death_times[ctr] = get_time() + ((uint64_t)(stats.time2die)) * 1000;
			if (*(kit_list[ctr].just_ate) > 1)
				*end_eats = *end_eats + 1;
			*(kit_list[ctr].just_ate) = 0;
		}
		pthread_mutex_unlock(kit_list[ctr].comms_mutex);
		if (control_tower_check4end(kit_list, death_times, &ctr, *end_eats))
			break ;
	}
	return (ctr);
}

void	control_tower(t_philokit *kit_list, t_stats stats)
{
	uint64_t	*death_times;
	int			end_eats;

	end_eats = 0;
	death_times = set_death_times(stats.num_philo, stats.time2die);
	while (1)
	{
		if (control_tower_routine(kit_list, stats, death_times, &end_eats) \
		== -2 || (end_eats >= stats.num_philo && stats.min_eats > 0))
		{
			free(death_times);
			break ;
		}
		usleep(50);
	}
}

static void	manage_threads(t_stats stats, t_philokit *kit_list, \
pthread_t *threads, uint64_t *start)
{
	int	ctr;

	ctr = -1;
	while (++ctr < stats.num_philo)
	{
		pthread_create(&threads[ctr], NULL, philoroutine, \
		(void *)(&(kit_list[ctr])));
	}
	ctr = -1;
	while (++ctr < stats.num_philo)
		pthread_mutex_lock(kit_list[ctr].comms_mutex);
	*start = get_time();
	ctr = -1;
	while (++ctr < stats.num_philo)
		pthread_mutex_unlock(kit_list[ctr].comms_mutex);
	control_tower(kit_list, stats);
	ctr = -1;
	while (++ctr < stats.num_philo)
	{
		pthread_join(threads[ctr], NULL);
		pthread_detach(threads[ctr]);
	}
}

void	prepare_threads(t_stats stats)
{
	t_philokit			*kit_list;
	pthread_mutex_t		*forks_list;
	pthread_mutex_t		*comms_mutex_list;
	pthread_t			*threads;
	uint64_t			start;

	start = 0;
	stats.start_time = &start;
	forks_list = create_forks(stats);
	comms_mutex_list = create_comms_mutex(stats);
	kit_list = create_kits(stats, forks_list, comms_mutex_list);
	threads = malloc(sizeof(pthread_t) * stats.num_philo);
	manage_threads(stats, kit_list, threads, &start);
	destroy_forks(stats, forks_list, comms_mutex_list);
	free(kit_list);
	free(threads);
}
