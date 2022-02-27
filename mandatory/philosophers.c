/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 18:14:31 by jvacaris          #+#    #+#             */
/*   Updated: 2022/02/27 23:07:46 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int parsing(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("Error: At least 4 arguments are required.\n");
		return (1);
	}
	if (positive_atoi(argv[1]) < 1 || positive_atoi(argv[1]) > 200)
	{
		printf("Error: Invalid amount of philosophers (1-200).\n");
		return (1);
	}
	if (positive_atoi(argv[2]) < 20 || positive_atoi(argv[3]) < 20 || \
	positive_atoi(argv[4]) < 20)
	{
		printf("Error: Invalid times (must be over 20ms).\n");
		return (1);
	}
	if (argc == 6 && positive_atoi(argv[5]) < 0)
	{
		printf("Error: Invalid last argument (must be over 0).\n");
		return (1);
	}
	return (0);
}

static t_stats	set_stats(int argc, char **argv)
{
	t_stats			stats;
	pthread_mutex_t	*prnt_key;
	pthread_mutex_t	*time_key;

	stats.num_philo = positive_atoi(argv[1]);
	stats.time2die = positive_atoi(argv[2]);
	stats.time2eat = positive_atoi(argv[3]);
	stats.time2sleep = positive_atoi(argv[4]);
	if (argc == 6)
		stats.min_eats = positive_atoi(argv[5]);
	else
		stats.min_eats = -1;
	prnt_key = malloc(sizeof(pthread_mutex_t));
	time_key = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(prnt_key, NULL);
	pthread_mutex_init(time_key, NULL);
	stats.printer_key = prnt_key;
	stats.timer_key = time_key;
	stats.start_time = NULL;
	return (stats);
}

int	main(int argc, char **argv)
{
	t_stats	stats;

	if (parsing(argc, argv))
		return (1);
	stats = set_stats(argc, argv);
	create_threads(stats);
}


/*
Everything seems to work, except for cases where *time2die* is too close to *time2sleep* + *time2eat*, but it shouldn't be a problem. 
Times get delayed over time way less than before. 
Libft still in use. 
minimum_times_each_philosopher_shoul_eat needs to be implemented.
*/