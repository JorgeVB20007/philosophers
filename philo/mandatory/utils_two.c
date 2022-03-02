/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 20:51:07 by jvacaris          #+#    #+#             */
/*   Updated: 2022/03/02 20:51:42 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	change_if_possible(t_philokit kit, int action, pthread_mutex_t *comms_mutex)
{
	int	returning;

	returning = 0;
	pthread_mutex_lock(comms_mutex);
	if (*(kit.status) == DEAD || *(kit.status) == STOP)
		returning = *(kit.status);
	else
		returning = action;
	pthread_mutex_unlock(comms_mutex);
	return (returning);
}

int	chk_int_with_mtx(int *nbr, pthread_mutex_t *cmms_mtx)
{
	int	returning;

	returning = 0;
	pthread_mutex_lock(cmms_mtx);
	returning = *nbr;
	pthread_mutex_unlock(cmms_mtx);
	return (returning);
}

uint64_t	chk_uint64t_with_mtx(uint64_t *nbr, pthread_mutex_t *cmms_mtx)
{
	uint64_t	returning;

	returning = 0;
	pthread_mutex_lock(cmms_mtx);
	returning = *nbr;
	pthread_mutex_unlock(cmms_mtx);
	return (returning);
}
