/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philoroutine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 18:14:29 by jvacaris          #+#    #+#             */
/*   Updated: 2022/02/28 23:43:50 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*only_one_philo(void *unformatted_kit)
{
	t_philokit	kit;

	kit = *((t_philokit *)unformatted_kit);
	pthread_mutex_lock(kit.left);
	printf("%6d %s%3d%s %s\n", 0, BOLD, kit.id, FMT_RST, FRK);
	ft_wait(kit.stats.time2die, kit.stats.timer_key, 0);
	printf("%6d %s%3d%s %s\n", kit.stats.time2die, BOLD, 1, FMT_RST, DIE);
	pthread_mutex_unlock(kit.left);
	return (NULL);
}

static int	eatingroutine(t_philokit *kit)
{
	pthread_mutex_lock(kit->right);
	printer(*kit, FRK_R);
	if (*(kit->status) == STOP)
	{
		pthread_mutex_unlock(kit->right);
		return (1);
	}
	pthread_mutex_lock(kit->left);
	*(kit->just_ate) = 1 + !(kit->times_eaten - kit->stats.min_eats);
	kit->times_eaten = kit->times_eaten + 1;
	printer(*kit, FRK_L);
	printer(*kit, EAT);
	if (*(kit->status) == STOP)
	{
		pthread_mutex_unlock(kit->right);
		pthread_mutex_unlock(kit->left);
		return (1);
	}
	*(kit->status) = change_if_possible(*kit, EATING);
	return (0);
}

void	*philoroutine(void *unformatted_kit)
{
	t_philokit	kit;
	uint64_t	delay;

	kit = *((t_philokit *)unformatted_kit);
	delay = 0;
	while (!(*(kit.stats.start_time)))
		usleep(5);
	if (!(kit.id % 2))
		usleep(5000);
	while (1)
	{
		if (eatingroutine(&kit))
			return (NULL);
		if (delay)
			delay = get_time() - delay;
		ft_wait(kit.stats.time2eat, kit.stats.timer_key, delay);
		delay = get_time();
		pthread_mutex_unlock(kit.right);
		pthread_mutex_unlock(kit.left);
		if (*(kit.status) == STOP)
			return (NULL);
		printer(kit, SLP);
		*(kit.status) = change_if_possible(kit, SLEEPING);
		delay = get_time() - delay;
		ft_wait(kit.stats.time2sleep, kit.stats.timer_key, delay);
		delay = get_time();
		if (*(kit.status) == STOP)
			return (NULL);
		printer(kit, TNK);
		*(kit.status) = change_if_possible(kit, THINKING);
	}
	return (NULL);
}
