/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philoroutine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 18:14:29 by jvacaris          #+#    #+#             */
/*   Updated: 2022/03/02 21:45:33 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	update_kit_status(t_philokit *kit, int new_status)
{
	pthread_mutex_lock(kit->comms_mutex);
	if (*(kit->status) != DEAD && *(kit->status) != STOP)
		*(kit->status) = new_status;
	pthread_mutex_unlock(kit->comms_mutex);
}

static int	eatingroutine(t_philokit *kit)
{
	pthread_mutex_lock(kit->right);
	printer(*kit, FRK);
	if (chk_int_with_mtx(kit->status, kit->comms_mutex) == STOP)
	{
		pthread_mutex_unlock(kit->right);
		return (1);
	}
	pthread_mutex_lock(kit->left);
	kit->times_eaten = kit->times_eaten + 1;
	pthread_mutex_lock(kit->comms_mutex);
	*(kit->just_ate) = 1 + !(kit->times_eaten - kit->stats.min_eats);
	pthread_mutex_unlock(kit->comms_mutex);
	printer(*kit, FRK);
	printer(*kit, EAT);
	if (chk_int_with_mtx(kit->status, kit->comms_mutex) == STOP)
	{
		pthread_mutex_unlock(kit->right);
		pthread_mutex_unlock(kit->left);
		return (1);
	}
	update_kit_status(kit, EATING);
	return (0);
}

static void	philoroutine_loop(t_philokit kit)
{
	uint64_t	delay;

	delay = 0;
	while (1)
	{
		if (eatingroutine(&kit))
			break ;
		if (delay)
			delay = get_time() - delay;
		ft_wait(kit.stats.time2eat, delay, kit.status, kit.comms_mutex);
		delay = get_time();
		pthread_mutex_unlock(kit.right);
		pthread_mutex_unlock(kit.left);
		if (chk_int_with_mtx(kit.status, kit.comms_mutex) == STOP)
			break ;
		printer(kit, SLP);
		update_kit_status(&kit, SLEEPING);
		delay = get_time() - delay;
		ft_wait(kit.stats.time2sleep, delay, kit.status, kit.comms_mutex);
		delay = get_time();
		if (chk_int_with_mtx(kit.status, kit.comms_mutex) == STOP)
			break ;
		printer(kit, TNK);
		update_kit_status(&kit, THINKING);
	}
}

void	*philoroutine(void *unformatted_kit)
{
	t_philokit	kit;

	kit = *((t_philokit *)unformatted_kit);
	while (!chk_uint64t_with_mtx(kit.stats.start_time, kit.comms_mutex))
		usleep(5);
	if (!(kit.id % 2))
		usleep(5000);
	philoroutine_loop(kit);
	return (NULL);
}
