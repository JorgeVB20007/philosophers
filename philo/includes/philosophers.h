/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 18:29:47 by jvacaris          #+#    #+#             */
/*   Updated: 2022/03/02 21:45:00 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# define FRK "has taken a fork"
# define EAT "\033[0;33mis eating\033[m"
# define SLP "\033[0;32mis sleeping\033[m"
# define TNK "\033[0;36mis thinking\033[m"
# define DIE "\033[1;31mdied\033[m"
# define BOLD "\033[1m"
# define FMT_RST "\033[m"

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <limits.h>
# include <stdint.h>
# include <sys/time.h>
//# include "../libft/libft.h"

typedef struct s_stats
{
	int					num_philo;
	int					time2die;
	int					time2eat;
	int					time2sleep;
	int					min_eats;
	pthread_mutex_t		*printer_key;
	pthread_mutex_t		*timer_key;
	uint64_t			*start_time;
}	t_stats;

typedef struct s_philokit
{
	int					id;
	int					temp_status;
	int					*status;
	int					times_eaten;
	int					temp_just_ate;
	int					*just_ate;
	pthread_mutex_t		*comms_mutex;
	pthread_mutex_t		*right;
	pthread_mutex_t		*left;
	t_stats				stats;
}	t_philokit;

enum	e_action_being_done
{
	DEAD,
	THINKING,
	EATING,
	SLEEPING,
	STOP
};

//* not_libft.c
int				ft_atoi(const char *str);
int				ft_strcmp(const char *s1, const char *s2);

//* parent_creators.c
pthread_mutex_t	*create_comms_mutex(t_stats stats);
pthread_mutex_t	*create_forks(t_stats stats);
void			destroy_forks(t_stats stats, pthread_mutex_t *fork_list, \
pthread_mutex_t *eats_list);
t_philokit		*create_kits(t_stats stats, pthread_mutex_t *forks, \
pthread_mutex_t *comms_mutex_list);

//* parent_utils.c
uint64_t		*set_death_times(int philos, int time2die);
void			stop_philos(t_philokit *kit_list);

//* parent.c
void			prepare_threads(t_stats stats);

//* philoroutine.c
void			*philoroutine(void *unformatted_kit);
void			*only_one_philo(void *unformatted_kit);

//*	mandatory/utils_one.c
void			ft_wait(int time, uint64_t delay, int *status, \
pthread_mutex_t *comms_mutex);
void			printer(t_philokit kit, char *action);
uint64_t		get_time(void);
int				positive_atoi(char *str);

//*	mandatory/utils_two.c
int				change_if_possible(t_philokit kit, int action, \
pthread_mutex_t *comms_mutex);
int				chk_int_with_mtx(int *nbr, pthread_mutex_t *cmms_mtx);
uint64_t		chk_uint64t_with_mtx(uint64_t *nbr, pthread_mutex_t *cmms_mtx);

#endif