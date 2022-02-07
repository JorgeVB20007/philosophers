/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 19:18:50 by jvacaris          #+#    #+#             */
/*   Updated: 2022/02/07 20:52:04 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/*
TODO	Make a delay compensator when using usleep by checking the initial and
TODO	final times. Record the current delay and discount it to the next usleep.
*/

static void	philoroutine(t_philokit kit)
{
	pthread_mutex_lock(kit.left);
	printer(kit, FRK_L);
	pthread_mutex_lock(kit.right);
	printer(kit, FRK_R);
	printer(kit, EAT);
	usleep(kit.input.time2eat * 1000);
	printer(kit, "is done eating");
	pthread_mutex_unlock(kit.right);
	pthread_mutex_unlock(kit.left);
	printer(kit, SLP);
	usleep(kit.input.time2sleep * 1000);
	printer(kit, TNK);
}

static void	*new_philo(void *unformatted_kit)
{
	t_philokit	kit;

	kit = *(t_philokit *)unformatted_kit;
	if (kit.id % 2 == 0)
	{
		usleep(10000);
	}
	while (1)
	{
		philoroutine(kit);
	}
	return (NULL);
}

void	create_philos(t_stats stats, pthread_mutex_t **mutex_lst)
{
	int	ctr;
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
