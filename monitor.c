/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:31:02 by trpham            #+#    #+#             */
/*   Updated: 2025/06/24 16:48:33 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_routine(void *arg)
{
	t_table *table;
	int		i;

	table = (t_table *)arg;
	while (1)
	{
		i = 0;
		while (i < table->no_philo)
		{
			pthread_mutex_lock(&table->philo_table[i].meal_lock);
			if (get_current_time() - table->philo_table[i].last_meal_time 
				>= table->philo_table[i].time_to_die)
			{
					table->dead_flag = TRUE;
					lock_and_printf(&table->philo_table[i], "died");
					pthread_mutex_unlock(&table->philo_table[i].meal_lock);
					return (NULL);
			}
			pthread_mutex_unlock(&table->philo_table[i].meal_lock);
			i++;
		}
		usleep(1000); //1 millisecond = 1000 microsecond
	}
	return (NULL);
}

