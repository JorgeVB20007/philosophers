#include "../includes/philosophers.h"

static pthread_mutex_t	*create_forks(t_stats stats)
{
	int				ctr;
	pthread_mutex_t	*mutex_list;

	ctr = -1;
	mutex_list = malloc(sizeof(pthread_mutex_t *) * stats.num_philo);
	while (++ctr < stats.num_philo)
	{
		pthread_mutex_init(&(mutex_list[ctr]), NULL);
	}
	return (mutex_list);
}

static t_philokit	*create_kits(t_stats stats, pthread_mutex_t *forks)
{
	t_philokit	*kit_list;
	int			ctr;

	ctr = -1;
	kit_list = malloc(sizeof(t_philokit *) * stats.num_philo);
	while (++ctr < stats.num_philo)
	{
		kit_list[ctr].id = ctr + 1;
		*(kit_list[ctr].status) = THINKING;
		kit_list[ctr].times_eaten = 0;
		kit_list[ctr].stats = stats;
		*(kit_list[ctr].just_ate) = 0;
		kit_list[ctr].left = &(forks[ctr]);
		if (ctr == 0)
			kit_list[ctr].right = &(forks[stats.num_philo - 1]);
		else
			kit_list[ctr].right = &(forks[ctr - 1]);
	}
	return (kit_list);
}

void	control_tower(t_philokit *kit_list, t_stats stats)
{
	int					ctr;
	unsigned long long	*death_times;
	unsigned long long	time;

	death_times = malloc(sizeof(unsigned long long) * stats.num_philo);
	while (1)
	{
		ctr = -1;
		time = get_time();
		while (++ctr < stats.num_philo)
		{
			if (*(kit_list[ctr].just_ate))
			{
				death_times[ctr] = get_time() + (unsigned long long)stats.time2die;
				*(kit_list[ctr].just_ate) = 0;
			}
			if (death_times[ctr] > time)
				*(kit_list[ctr].status) = DEAD;
		}
	}
}

void	create_threads(t_stats stats)
{
	int				ctr;
	t_philokit		*kit_list;
	pthread_mutex_t	*forks_list;
	pthread_t		*threads;

	ctr = -1;
	forks_list = create_forks(stats);
	kit_list = create_kits(stats, forks_list);
	threads = malloc(sizeof(pthread_t *) * stats.num_philo);
	while (++ctr < stats.num_philo)
	{
		pthread_create(&(threads[ctr]), NULL, (IDK), (void *)kit_list);
	}
}
