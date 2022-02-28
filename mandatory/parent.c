/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 18:14:20 by jvacaris          #+#    #+#             */
/*   Updated: 2022/02/28 23:51:53 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static pthread_mutex_t	*create_forks(t_stats stats)
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

static t_philokit	*create_kits(t_stats stats, pthread_mutex_t *forks)
{
	t_philokit	*kit_list;
	int			ctr;

	ctr = -1;
	kit_list = malloc(sizeof(t_philokit) * stats.num_philo);
	while (++ctr < stats.num_philo)
	{
//		kit_list[ctr] = malloc(sizeof(t_philokit));
		kit_list[ctr].id = ctr + 1;
		kit_list[ctr].temp_status = THINKING;
		kit_list[ctr].status = &(kit_list[ctr].temp_status);		// ? This might be unnecessary.
		kit_list[ctr].times_eaten = 0;
		kit_list[ctr].stats = stats;
		kit_list[ctr].temp_just_ate = 0;
		kit_list[ctr].just_ate = &(kit_list[ctr].temp_just_ate);	// ? This might be unnecessary.
		kit_list[ctr].left = &(forks[ctr]);
		if (ctr == 0)
			kit_list[ctr].right = &(forks[stats.num_philo - 1]);
		else
			kit_list[ctr].right = &(forks[ctr - 1]);
	}
	return (kit_list);
}

static uint64_t	*set_death_times(int philos, int time2die/*, pthread_mutex_t *timer_key*/)
{
	int	a;
	uint64_t	*death_times;

	a = 0;
	death_times = malloc(sizeof(uint64_t) * philos);
	while (a < philos)
	{
		death_times[a] = get_time(/*timer_key*/) + ((uint64_t)time2die * 1000);
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
		*(kit_list[a].status) = change_if_possible(kit_list[a], STOP);
		a++;
	}
}

void	control_tower(t_philokit *kit_list, t_stats stats)
{
	int			ctr;
	uint64_t	*death_times;
	uint64_t	time;
	int			end_eats;

	end_eats = 0;
	death_times = set_death_times(stats.num_philo, stats.time2die/*, stats.timer_key*/);
	while (1)
	{
		ctr = -1;
		while (++ctr < stats.num_philo)
		{
			time = get_time(/*stats.timer_key*/);
			if (*(kit_list[ctr].just_ate) > 0)
			{
				death_times[ctr] = get_time(/*stats.timer_key*/)/*time*/ + ((uint64_t)(stats.time2die)) * 1000;
				if (*(kit_list[ctr].just_ate) > 1)
				{
					end_eats++;
					printf("\n\nSOMEONE FINISHED. End eats = %d\n\n", end_eats);
				}
				*(kit_list[ctr].just_ate) = 0;
			}
			else if (death_times[ctr] < time)
			{
				pthread_mutex_lock(kit_list[0].stats.timer_key);
				stop_philos(kit_list);
				*(kit_list[ctr].status) = DEAD;
				pthread_mutex_unlock(kit_list[0].stats.timer_key);
				printer((kit_list[ctr]), DIE);
				ctr = -2;
				break ;
			}
			if (end_eats >= stats.num_philo)
			{
				pthread_mutex_lock(kit_list[0].stats.timer_key);
				stop_philos(kit_list);
				pthread_mutex_unlock(kit_list[0].stats.timer_key);
				break ;
			}
		}
//		printf(" %d %d\n", end_eats, stats.min_eats);
		if (ctr == -2 || (end_eats >= stats.min_eats && stats.min_eats > 0))
			break ;
		usleep(100);
//		printf("\n%llu\n", get_time());
	}
}

void	create_threads(t_stats stats)
{
	int					ctr;
	t_philokit			*kit_list;
	pthread_mutex_t		*forks_list;
	pthread_t			*threads;
	uint64_t	start;

	ctr = -1;
	start = 0;
	stats.start_time = &start;
	forks_list = create_forks(stats);
	kit_list = create_kits(stats, forks_list);
	threads = malloc(sizeof(pthread_t) * stats.num_philo);
	if (stats.num_philo == 1)
	{
		pthread_create(&threads[ctr], NULL, only_one_philo, (void *)(&(kit_list[0])));
		pthread_join(threads[ctr], NULL);
		return ;
	}
	while (++ctr < stats.num_philo)
	{
		pthread_create(&threads[ctr], NULL, philoroutine, (void *)(&(kit_list[ctr])));
	}
	ctr = -1;
	start = get_time(/*stats.timer_key*/);
	control_tower(kit_list, stats);
	while (++ctr < stats.num_philo)
	{
		pthread_join(threads[ctr], NULL);
	}
}
