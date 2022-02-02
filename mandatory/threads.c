/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 19:18:50 by jvacaris          #+#    #+#             */
/*   Updated: 2022/02/02 23:22:35 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*new_philo(void *unformatted_kit)
{
	t_philokit	kit;

	write(1, "/", 1);
	kit = *(t_philokit *)unformatted_kit;
	write(1, ")", 1);
	printf("NEW PHILO (#%d)\n", kit.id);
	write(1, "(", 1);

	return (NULL);
}


void	create_philos(t_stats stats, pthread_mutex_t **mutex_lst)
{
	int			ctr;
	t_philokit	new_kit;
	pthread_t	**philolist;
	pthread_t	*one_philo;

	ctr = 0;
	philolist = malloc(sizeof(pthread_t) * (stats.num_philo + 1));
	one_philo = NULL;
	while (ctr++ < stats.num_philo)
	{
		write(1, "@", 1);
		new_kit.id = ctr;
		new_kit.left = mutex_lst[ctr - 1];
		write(1, "$", 1);
		if (ctr == 1)
			new_kit.right = mutex_lst[stats.num_philo - 1];
		else
			new_kit.right = mutex_lst[ctr - 2];
		write(1, "%%", 1);
		pthread_create(one_philo, NULL, new_philo, &new_kit);
		write(1, "&", 1);
	}
}
