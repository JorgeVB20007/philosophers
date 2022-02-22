/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 19:47:02 by jvacaris          #+#    #+#             */
/*   Updated: 2022/02/21 21:21:51 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	printer(t_philokit kit, char *action, unsigned long long time)
{
	if (*(kit.someone_died) >= 0 && *(kit.someone_died) < kit.input.num_philo)
	{
		pthread_mutex_lock(kit.input.printer_key);
		time = get_time(kit);
		printf("\n%llu\n", get_time(kit));
		printf("%6llu %s%d%s %s %p\n", (time - kit.input.start_time), \
		BOLD, kit.id, FMT_RST, action, kit.input.printer_key);
		printf("someone_died = %d\n", *(kit.someone_died));
		pthread_mutex_unlock(kit.input.printer_key);
	}
	else if (!ft_strcmp(action, DIE))
		*(kit.someone_died) = -1;
}

void	printer_str(pthread_mutex_t *key, char *text)
{
	pthread_mutex_lock(key);
	ft_putstr_fd(text, 1);
	pthread_mutex_unlock(key);
}

void	printer_num(pthread_mutex_t *key, int num)
{
	pthread_mutex_lock(key);
	ft_putnbr_fd(num, 1);
	pthread_mutex_unlock(key);
}
