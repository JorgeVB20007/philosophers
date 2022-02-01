/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 18:29:46 by jvacaris          #+#    #+#             */
/*   Updated: 2022/02/01 21:30:02 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

t_stats	set_struct(int argc, char **argv)
{
	t_stats	stats;

	stats.num_philo = positive_atoi(argv[1]);
	stats.time2die = positive_atoi(argv[2]);
	stats.time2eat = positive_atoi(argv[3]);
	stats.time2sleep = positive_atoi(argv[4]);
	if (argc == 6)
		stats.min_eats = positive_atoi(argv[5]);
	else
		stats.min_eats = -1;
	return (stats);
}

int	main(int argc, char **argv)
{
	t_stats	stats;
	struct timeval tval;

	if (argc < 5 || argc > 6)
		return (1);
	stats = set_struct(argc, argv);
	printf("num_philo %d; time2die %d; time2eat %d; time2sleep %d; min_eats %d;", \
	stats.num_philo, stats.time2die, stats.time2eat, stats.time2sleep, stats.min_eats);
	return (0);
}
