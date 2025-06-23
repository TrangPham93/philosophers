/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:31:02 by trpham            #+#    #+#             */
/*   Updated: 2025/06/23 17:35:00 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (get_current_time() - philo->last_meal_time >= philo->time_to_die)
		{
			lock_and_printf(philo, "died");
			philo->dead_flag = TRUE;
			break ;
		}
		ft_usleep(10);
	}
	return (NULL);
}