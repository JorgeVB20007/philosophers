/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 17:59:12 by jvacaris          #+#    #+#             */
/*   Updated: 2022/02/13 20:10:46 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	*death_while_waiting(void *unformatted_kit)
{
	t_philokit	kit;
	unsigned long long		time;

	kit = *(t_philokit *)unformatted_kit;
	while (*(kit.waiting4mutex) && !is_ok_to_end(kit))
	{
		time = get_time(kit);
		if (time >= kit.time4death)
		{
			printer(kit, DIE, time);
			*(kit.someone_died) = -1;
			return (NULL);
		}
		usleep(50);
	}
	return (NULL);
}

static void	stopped_sleeping(t_philokit *kit, unsigned long long *time, \
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
	*time = get_time(*kit);
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
	*time = get_time(*kit);
	printer(*kit, FRK, *time);
	kit->status = EATING;
	kit->time4end = *time + kit->input.time2eat;
	kit->time4death = *time + kit->input.time2die;
	printer(*kit, EAT, *time);
}

static void	timesup(t_philokit *kit, unsigned long long time)
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

static void	unlock_if_eating(t_philokit *kit)
{
	if ((*kit).status == EATING)
	{
		pthread_mutex_unlock((*kit).left);
		pthread_mutex_unlock((*kit).right);
		(*kit).status = -1;
	}
}

void	*new_philo(void *unformatted_kit)
{
	t_philokit	kit;
	unsigned long long		time;

	kit = *(t_philokit *)unformatted_kit;
	kit.time4end = get_time(kit);
	if (kit.id % 2 == 0)
		usleep(100);
	while (!is_ok_to_end(kit))
	{
		time = get_time(kit);
		if (time >= kit.time4end && kit.input.num_philo > 1)
			timesup(&kit, time);
		else if (time >= kit.time4death)
		{
			printer(kit, DIE, time);
			*(kit.someone_died) = -1;
			return (NULL);
		}
		usleep(50);
	}
	unlock_if_eating(&kit);
	return (NULL);
}
