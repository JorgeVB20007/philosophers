/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 18:14:31 by jvacaris          #+#    #+#             */
/*   Updated: 2022/03/02 21:45:47 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	parsing(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		if (argc < 5)
			printf("Error: At least 4 arguments are required.\n");
		if (argc > 6)
			printf("Error: No more than 6 arguments must be given.\n");
		return (1);
	}
	if (positive_atoi(argv[1]) < 1 || positive_atoi(argv[1]) > 200)
	{
		printf("Error: Invalid amount of philosophers (1-200).\n");
		return (1);
	}
	if (positive_atoi(argv[2]) < 50 || positive_atoi(argv[3]) < 50 || \
	positive_atoi(argv[4]) < 50)
	{
		printf("Error: Invalid times (must be an int over 50ms).\n");
		return (1);
	}
	if (argc == 6 && positive_atoi(argv[5]) <= 0)
	{
		printf("Error: Invalid last argument (must be an int over 0).\n");
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

void	*singlephilo_thread(void *unformatted_kit)
{
	t_philokit	kit;

	kit = *((t_philokit *)unformatted_kit);
	pthread_mutex_lock(kit.left);
	printf("%6d %s%3d%s %s\n", 0, BOLD, 1, FMT_RST, FRK);
	ft_wait(kit.stats.time2die, 0, NULL, NULL);
	printf("%6d %s%3d%s %s\n", kit.stats.time2die, BOLD, 1, FMT_RST, DIE);
	return (NULL);
}

static void	singlephilo(t_stats stats)
{
	t_philokit		kit;
	pthread_mutex_t	*fork;
	pthread_t		*thread;

	fork = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(fork, NULL);
	kit.left = fork;
	kit.stats = stats;
	thread = malloc(sizeof(thread));
	pthread_create(thread, NULL, singlephilo_thread, (void *)(&kit));
	pthread_join(*thread, NULL);
	pthread_detach(*thread);
	free(thread);
	free(fork);
}

int	main(int argc, char **argv)
{
	t_stats	stats;

	if (parsing(argc, argv))
		return (1);
	stats = set_stats(argc, argv);
	if (stats.num_philo == 1)
		singlephilo(stats);
	else
		prepare_threads(stats);
	pthread_mutex_destroy(stats.printer_key);
	pthread_mutex_destroy(stats.timer_key);
	free(stats.printer_key);
	free(stats.timer_key);
}
