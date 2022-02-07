/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 18:29:47 by jvacaris          #+#    #+#             */
/*   Updated: 2022/02/07 20:45:56 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# define FRK_R "has taken their right fork"
# define FRK_L "has taken their left fork"
# define FRK "has taken a fork" 
# define EAT "is eating"
# define SLP "is sleeping"
# define TNK "is thinking"
# define DIE "died"

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include "../libft/libft.h"

typedef struct s_stats
{
	int				num_philo;
	int				time2die;
	int				time2eat;
	int				time2sleep;
	int				min_eats;
	pthread_mutex_t	*printer_key;
	long			start_time;
}	t_stats;

typedef struct s_philokit
{
	int				id;
	pthread_mutex_t	*right;
	pthread_mutex_t	*left;
	t_stats			input;
}	t_philokit;

int		positive_atoi(char *str);
long	get_time(void);
void	create_philos(t_stats stats, pthread_mutex_t **mutex_lst);
void	printer_str(pthread_mutex_t *key, char *text);
void	printer_num(pthread_mutex_t *key, int num);
void	printer(t_philokit kit, char *action);

#endif