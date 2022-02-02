/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 18:29:47 by jvacaris          #+#    #+#             */
/*   Updated: 2022/02/02 22:42:42 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include "../libft/libft.h"

typedef struct s_stats
{
	int	num_philo;
	int	time2die;
	int	time2eat;
	int	time2sleep;
	int	min_eats;
}	t_stats;

typedef struct	s_philokit
{
	int				id;
	pthread_mutex_t *right;
	pthread_mutex_t	*left;
}	t_philokit;

int		positive_atoi(char *str);
void	create_philos(t_stats stats, pthread_mutex_t **mutex_lst);

#endif