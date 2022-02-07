/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 19:47:02 by jvacaris          #+#    #+#             */
/*   Updated: 2022/02/07 20:46:15 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	printer(t_philokit kit, char *action)
{
	pthread_mutex_lock(kit.input.printer_key);
	printf("%ld %d %s\n", ((get_time() - kit.input.start_time)), kit.id, action);
	pthread_mutex_unlock(kit.input.printer_key);
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
