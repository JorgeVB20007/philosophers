/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 19:18:50 by jvacaris          #+#    #+#             */
/*   Updated: 2022/02/13 19:30:05 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/*
?	Deaths need to be checked somewhere else or a philo will not die until 
?	they get a fork unless they're sleeping or eating.
*/

static t_philokit	*set_the_kit(t_stats stats, pthread_mutex_t **mutex_lst, \
int ctr, int *someone_died)
{
	t_philokit	*new_kit;

	new_kit = malloc(sizeof(t_philokit));
	new_kit->id = ctr + 1;
	new_kit->input = stats;
	if (stats.num_philo == 1)
		new_kit->left = NULL;
	else
		new_kit->left = mutex_lst[ctr];
	new_kit->status = SLEEPING;
	new_kit->someone_died = someone_died;
	new_kit->time4death = get_time(*new_kit) + stats.time2die;
	new_kit->times_eaten = 0;
	if (!ctr)
		new_kit->right = mutex_lst[stats.num_philo - 1];
	else
		new_kit->right = mutex_lst[ctr - 1];
	return (new_kit);
}

void	create_philos(t_stats stats, pthread_mutex_t **mutex_lst, int ctr)
{
	t_philokit	**new_kit;
	pthread_t	**philolist;
	int			someone_died;

	someone_died = 0;
	philolist = malloc(sizeof(pthread_t *) * stats.num_philo);
	new_kit = malloc(sizeof(t_philokit *) * stats.num_philo);
	while (++ctr < stats.num_philo)
	{
		new_kit[ctr] = set_the_kit(stats, mutex_lst, ctr, &someone_died);
		philolist[ctr] = malloc(sizeof(pthread_t));
		pthread_create(philolist[ctr], NULL, new_philo, new_kit[ctr]);
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
