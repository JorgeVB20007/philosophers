/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 19:18:50 by jvacaris          #+#    #+#             */
/*   Updated: 2022/02/12 23:24:17 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/*
?	Deaths need to be checked somewhere else or a philo will not die until 
?	they get a fork unless they're sleeping or eating.
*/

static void	*death_while_waiting(void *unformatted_kit)
{
	t_philokit	kit;
	long		time;

	kit = *(t_philokit *)unformatted_kit;
	while (*(kit.waiting4mutex) && !is_ok_to_end(kit))
	{
		time = get_time();
		if (time >= kit.time4death)
		{
			*(kit.someone_died) = -1;
			printer(kit, DIE, time);
			return (NULL);
		}
		usleep(50);
	}
	return (NULL);
}

static void	stopped_sleeping(t_philokit *kit, long *time, \
pthread_t thread_while_waiting)
{
	*(kit->waiting4mutex) = 1;
	pthread_create(&thread_while_waiting, NULL, death_while_waiting, kit);
	pthread_mutex_lock(kit->right);
	if (is_ok_to_end(*kit))
	{
		pthread_mutex_unlock(kit->right);
		return ;
	}
	*time = get_time();
	printer(*kit, FRK, *time);
	pthread_mutex_lock(kit->left);
	*(kit->waiting4mutex) = 0;
	pthread_join(thread_while_waiting, NULL);
	if (is_ok_to_end(*kit))
	{
		pthread_mutex_unlock(kit->right);
		pthread_mutex_unlock(kit->left);
		return ;
	}
	*time = get_time();
	printer(*kit, FRK, *time);
	kit->status = EATING;
	kit->time4end = *time + kit->input.time2eat;
	kit->time4death = *time + kit->input.time2die;
	printer(*kit, EAT, *time);
}

static void	timesup(t_philokit *kit, long time)
{
	int			waiting4mutex;

	waiting4mutex = 0;
	kit->waiting4mutex = &waiting4mutex;
	if (kit->status == EATING)
	{
		kit->times_eaten = kit->times_eaten + 1;
		if (kit->times_eaten == kit->input.min_eats)
			(*(kit->someone_died))++;
		if (is_ok_to_end(*kit))
			return ;
		printer(*kit, SLP, time);
		pthread_mutex_unlock(kit->right);
		pthread_mutex_unlock(kit->left);
		kit->status = SLEEPING;
		kit->time4end = time + kit->input.time2sleep;
	}
	else if (kit->status == SLEEPING)
	{
		kit->status = THINKING;
		printer(*kit, TNK, time);
		stopped_sleeping(kit, &time, NULL);
	}
}

static void	*new_philo(void *unformatted_kit)
{
	t_philokit	kit;
	long		time;

	kit = *(t_philokit *)unformatted_kit;
	kit.time4end = get_time();
	if (kit.id % 2 == 0)
		usleep(100);
	while (!is_ok_to_end(kit))
	{
		time = get_time();
		if (time >= kit.time4end && kit.input.num_philo > 1)
			timesup(&kit, time);
		else if (time >= kit.time4death)
		{
			*(kit.someone_died) = -1;
			printer(kit, DIE, time);
			return (NULL);
		}
		usleep(50);
	}
	if (kit.status == EATING)
	{
		pthread_mutex_unlock(kit.left);
		pthread_mutex_unlock(kit.right);
		kit.status = -1;
	}
	return (NULL);
}

void	create_philos(t_stats stats, pthread_mutex_t **mutex_lst)
{
	int			ctr;
	t_philokit	**new_kit;
	pthread_t	**philolist;
	int			someone_died;

	ctr = 0;
	someone_died = 0;
	philolist = malloc(sizeof(pthread_t *) * stats.num_philo);
	new_kit = malloc(sizeof(t_philokit *) * stats.num_philo);
	while (ctr < stats.num_philo)
	{
		new_kit[ctr] = malloc(sizeof(t_philokit));
		philolist[ctr] = malloc(sizeof(pthread_t));
		(new_kit[ctr])->id = ctr + 1;
		if (stats.num_philo == 1)
			(new_kit[ctr])->left = NULL;
		else
			(new_kit[ctr])->left = mutex_lst[ctr];
		(new_kit[ctr])->status = SLEEPING;
		(new_kit[ctr])->someone_died = &someone_died;
		(new_kit[ctr])->time4death = get_time() + stats.time2die;
		(new_kit[ctr])->times_eaten = 0;
		if (!ctr)
			(new_kit[ctr])->right = mutex_lst[stats.num_philo - 1];
		else
			(new_kit[ctr])->right = mutex_lst[ctr - 1];
		(new_kit[ctr])->input = stats;
		pthread_create(philolist[ctr], NULL, new_philo, new_kit[ctr]);
		ctr++;
	}
	ctr = -1;
	while (++ctr < stats.num_philo)
	{
		pthread_join(*(philolist[ctr]), NULL);
		free(new_kit[ctr]);
	}
	ctr = -1;
	while (++ctr < stats.num_philo)
		free(philolist[ctr]);
	free(new_kit);
	free(philolist);
}
