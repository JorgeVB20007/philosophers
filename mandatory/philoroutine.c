/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philoroutine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 18:14:29 by jvacaris          #+#    #+#             */
/*   Updated: 2022/02/23 23:10:39 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

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
	printer(*kit, FRK_L);
	printer(*kit, EAT);
	if (*(kit->status) == STOP)
	{
		pthread_mutex_unlock(kit->right);
		pthread_mutex_unlock(kit->left);
		return (1);
	}
	*(kit->status) = change_if_possible(*kit, EATING);
	*(kit->just_ate) = 1;
	return (0);
}

void	*philoroutine(void *unformatted_kit)
{
	t_philokit	kit;

	kit = *((t_philokit *)unformatted_kit);
//	printf("Philo %d just started!\n", kit.id);
//	ft_wait(100);
//	printf(" (%d)  <- %p %p ->\n", kit.id, kit.left, kit.right);
	if (!(kit.id % 2))
		ft_wait(10);
	while (1)
	{
		if (eatingroutine(&kit))
			return (NULL);
		ft_wait(kit.stats.time2eat);
		pthread_mutex_unlock(kit.right);
		pthread_mutex_unlock(kit.left);
		if (*(kit.status) == STOP)
			return (NULL);
		printer(kit, SLP);
		*(kit.status) = change_if_possible(kit, SLEEPING);
		ft_wait(kit.stats.time2sleep);
		if (*(kit.status) == STOP)
			return (NULL);
		printer(kit, TNK);
		*(kit.status) = change_if_possible(kit, THINKING);
	}
	return (NULL);
}