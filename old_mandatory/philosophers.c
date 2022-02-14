/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 18:29:46 by jvacaris          #+#    #+#             */
/*   Updated: 2022/02/13 19:28:51 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

// TODO		gcc -Wall -Werror -Wextra libft/libft.a mandatory/*.c  -o philo

static t_stats	set_struct(int argc, char **argv)
{
	t_stats			stats;
	pthread_mutex_t	key_mkr;
	pthread_mutex_t	key2_mkr;

	stats.num_philo = positive_atoi(argv[1]);
	stats.time2die = positive_atoi(argv[2]);
	stats.time2eat = positive_atoi(argv[3]);
	stats.time2sleep = positive_atoi(argv[4]);
	if (argc == 6)
		stats.min_eats = positive_atoi(argv[5]);
	else
		stats.min_eats = -2;
	pthread_mutex_init(&key_mkr, NULL);
	pthread_mutex_init(&key2_mkr, NULL);
	stats.printer_key = &key_mkr;
	stats.time_key = &key2_mkr;
	stats.start_time = get_time2();
	return (stats);
}

static int	check_input_validity(t_stats stats)
{
	if (stats.num_philo < 1)
	{
		printf("Error: At least one philosopher is required.\n");
		return (1);
	}
	if (stats.num_philo > 200)
	{
		printf("Error: Max amount of philosophers is 200.\n");
		return (1);
	}
	if (stats.time2die < 1 || stats.time2eat < 1 || stats.time2sleep < 1 || \
	stats.min_eats == -1)
	{
		printf("Four or five numeric arguments (1 - 2^31-1) are required.\n");
		return (1);
	}
	return (0);
}

static pthread_mutex_t	**create_mutexes(int num_philo)
{
	pthread_mutex_t	**mutex_lst;
	int				ctr;
	pthread_mutex_t	*new_mutex;

	ctr = -1;
	mutex_lst = malloc(sizeof(pthread_mutex_t *) * (num_philo + 1));
	while (++ctr < num_philo)
	{
		new_mutex = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(new_mutex, NULL);
		mutex_lst[ctr] = new_mutex;
	}
	mutex_lst[ctr] = NULL;
	return (mutex_lst);
}

static void	destroy_mutexes(t_stats *stats, pthread_mutex_t ***mutex_lst)
{
	int				ctr;

	ctr = -1;
	while (++ctr < (*stats).num_philo)
	{
		pthread_mutex_destroy((*mutex_lst)[ctr]);
		free((*mutex_lst)[ctr]);
	}
	pthread_mutex_destroy((*stats).printer_key);
	free((*mutex_lst)[ctr]);
	free(*mutex_lst);
}

int	main(int argc, char **argv)
{
	t_stats			stats;
	pthread_mutex_t	**mutex_lst;

	if (argc < 5 || argc > 6)
	{
		printf("Error: At least 4 arguments are required.\n");
		return (1);
	}
	stats = set_struct(argc, argv);
	if (check_input_validity(stats))
		return (1);
	mutex_lst = create_mutexes(stats.num_philo);
	create_philos(stats, mutex_lst, -1);
	destroy_mutexes(&stats, &mutex_lst);
	system("leaks philo");
	return (0);
}

// TODO		gcc -Wall -Werror -Wextra libft/libft.a mandatory/*.c  -o philo
