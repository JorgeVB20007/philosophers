/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philoroutine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 18:14:29 by jvacaris          #+#    #+#             */
/*   Updated: 2022/02/21 21:41:01 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*philoroutine(void *unformatted_kit)
{
	t_philokit	kit;

	kit = *((t_philokit *)unformatted_kit);
	printf("Philo %d just started!\n", kit.id);
//	ft_wait(100);
	if (!(kit.id % 2))
		ft_wait(10);
	while (1)
	{
		pthread_mutex_lock(kit.right);
		printer(kit, FRK_R);
		pthread_mutex_lock(kit.left);
		printer(kit, FRK_L);
		printer(kit, EAT);
		*(kit.status) = EATING;
		*(kit.just_ate) = 1;
		ft_wait(kit.stats.time2eat);
		pthread_mutex_unlock(kit.right);
		pthread_mutex_unlock(kit.left);
		printer(kit, SLP);
		*(kit.status) = SLEEPING;
		ft_wait(kit.stats.time2sleep);
		printer(kit, TNK);
		*(kit.status) = THINKING;
	}
	return (NULL);
}