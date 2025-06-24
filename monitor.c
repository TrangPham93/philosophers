/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:31:02 by trpham            #+#    #+#             */
/*   Updated: 2025/06/24 18:20:14 by trpham           ###   ########.fr       */
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
		i = -1;
		while (++i < table->no_philo)
		{
			pthread_mutex_lock(&table->philo_table[i].meal_lock);
			if (get_current_time() - table->philo_table[i].last_meal_time 
				>= table->philo_table[i].time_to_die)
			{
				pthread_mutex_lock(&table->dead_lock);
				table->dead_flag = TRUE;
				pthread_mutex_unlock(&table->dead_lock);
				lock_and_print_death(&table->philo_table[i]);
				pthread_mutex_unlock(&table->philo_table[i].meal_lock);
				return (NULL);
			}
			pthread_mutex_unlock(&table->philo_table[i].meal_lock);
		}
		usleep(1000); //1 millisecond = 1000 microsecond
	}
	return (NULL);
}

