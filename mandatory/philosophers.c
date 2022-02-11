/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 18:29:46 by jvacaris          #+#    #+#             */
/*   Updated: 2022/02/11 21:59:07 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

// TODO		gcc -Wall -Werror -Wextra libft/libft.a mandatory/*.c  -o philo

static t_stats	set_struct(int argc, char **argv)
{
	t_stats			stats;
	pthread_mutex_t	key_mkr;

	stats.num_philo = positive_atoi(argv[1]);
	stats.time2die = positive_atoi(argv[2]);
	stats.time2eat = positive_atoi(argv[3]);
	stats.time2sleep = positive_atoi(argv[4]);
	if (argc == 6)
		stats.min_eats = positive_atoi(argv[5]);
	else
		stats.min_eats = -1;
	pthread_mutex_init(&key_mkr, NULL);
	stats.printer_key = &key_mkr;
	stats.start_time = get_time();
	return (stats);
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
		printf("%p\n", mutex_lst[ctr]);
	}
	mutex_lst[ctr] = NULL;
	return (mutex_lst);
}

static void	destroy_mutexes(int num_philo, pthread_mutex_t ***mutex_lst)
{
	int				ctr;

	ctr = -1;
	while (++ctr < num_philo)
	{
		pthread_mutex_destroy((*mutex_lst)[ctr]);
		free((*mutex_lst)[ctr]);
	}
	free((*mutex_lst)[ctr]);
	free(*mutex_lst);
}

int	main(int argc, char **argv)
{
	t_stats			stats;
	pthread_mutex_t	**mutex_lst;

	if (argc < 5 || argc > 6)
		return (1);
	stats = set_struct(argc, argv);
	mutex_lst = create_mutexes(stats.num_philo);
	create_philos(stats, mutex_lst);
	destroy_mutexes(stats.num_philo, &mutex_lst);
//	system("leaks philo");
	return (0);
}

// TODO		gcc -Wall -Werror -Wextra libft/libft.a mandatory/*.c  -o philo
