/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 18:29:47 by jvacaris          #+#    #+#             */
/*   Updated: 2022/02/12 23:06:09 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# define FRK_R "has taken their right fork"
# define FRK_L "has taken their left fork"
# define FRK "has taken a fork"
# define EAT "\033[0;33mis eating\033[m"
# define SLP "\033[0;32mis sleeping\033[m"
# define TNK "\033[0;36mis thinking\033[m"
# define DIE "\033[1;31mdied\033[m"

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
	long			time4death;
	long			time4end;
	int				status;
	int				times_eaten;
	int				*someone_died;
	int				*waiting4mutex;
	pthread_mutex_t	*right;
	pthread_mutex_t	*left;
	t_stats			input;
}	t_philokit;

enum	e_action_being_done
{
	DEAD,
	THINKING,
	EATING,
	SLEEPING
};

//*	mandatory/printer.c
void	printer_str(pthread_mutex_t *key, char *text);
void	printer_num(pthread_mutex_t *key, int num);
void	printer(t_philokit kit, char *action, long time);

//*	mandatory/threads.c
void	create_philos(t_stats stats, pthread_mutex_t **mutex_lst);

//*	mandatory/utils.c
long	get_time(void);
int		positive_atoi(char *str);
int		is_ok_to_end(t_philokit kit);

#endif