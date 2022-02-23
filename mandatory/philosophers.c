/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 18:14:31 by jvacaris          #+#    #+#             */
/*   Updated: 2022/02/23 22:21:08 by jvacaris         ###   ########.fr       */
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
	pthread_mutex_t	key;

	stats.num_philo = positive_atoi(argv[1]);
	stats.time2die = positive_atoi(argv[2]);
	stats.time2eat = positive_atoi(argv[3]);
	stats.time2sleep = positive_atoi(argv[4]);
	if (argc == 6)
		stats.min_eats = positive_atoi(argv[5]);
	else
		stats.min_eats = -1;
	pthread_mutex_init(&key, NULL);
	stats.printer_key = &key;
	stats.start_time = get_time();
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
