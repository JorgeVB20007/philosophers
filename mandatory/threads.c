/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 19:18:50 by jvacaris          #+#    #+#             */
/*   Updated: 2022/02/09 22:00:28 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/*
?	Deaths need to be checked somewhere else or a philo will not die until 
?	they get a fork unless they're sleeping or eating.
*/

static void	timesup(t_philokit *kit, long time)
{
	if (kit->status == EATING)
	{
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
		pthread_mutex_lock(kit->right);
		time = get_time();
		printer(*kit, FRK, time);
		pthread_mutex_lock(kit->left);
		time = get_time();
		printer(*kit, FRK, time);
		kit->status = EATING;
		kit->time4end = time + kit->input.time2eat;
		kit->time4death = time + kit->input.time2die;
		printer(*kit, EAT, time);
	}
}

static void	*new_philo(void *unformatted_kit)
{
	t_philokit	kit;
	long		time;

	time = get_time();
	kit = *(t_philokit *)unformatted_kit;
	kit.time4end = time;
	if (kit.id % 2 == 0)
	{
		usleep(100);
	}
	while (1)
	{
		time = get_time();
		if (time >= kit.time4end)
			timesup(&kit, time);
		if (kit.id == 1)
			write(1, ".", 1);
		if (kit.id == 2)
			write(1, "-", 1);
		usleep(50);
	}
	return (NULL);
}

void	create_philos(t_stats stats, pthread_mutex_t **mutex_lst)
{
	int			ctr;
	t_philokit	**new_kit;
	pthread_t	*philolist;

	ctr = 0;
	philolist = malloc(sizeof(pthread_t) * stats.num_philo + 1);
	new_kit = malloc(sizeof(t_philokit *) * stats.num_philo + 1);
	while (ctr < stats.num_philo)
	{
		new_kit[ctr] = malloc(sizeof(t_philokit));
		(new_kit[ctr])->id = ctr + 1;
		(new_kit[ctr])->left = mutex_lst[ctr];
		(new_kit[ctr])->status = SLEEPING;
		if (!ctr)
			(new_kit[ctr])->right = mutex_lst[stats.num_philo - 1];
		else
			(new_kit[ctr])->right = mutex_lst[ctr - 1];
		(new_kit[ctr])->input = stats;
		pthread_create(&(philolist[ctr]), NULL, new_philo, new_kit[ctr]);
		ctr++;
	}
	ctr = 0;
	while (ctr < stats.num_philo)
	{
		pthread_join(philolist[ctr++], NULL);
	}
}
