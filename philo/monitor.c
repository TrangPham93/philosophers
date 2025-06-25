/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:31:02 by trpham            #+#    #+#             */
/*   Updated: 2025/06/25 18:28:34 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	monitor_routine(t_table *table)
{
	// t_table *table;

	// table = (t_table *)arg;
	while (1)
	{
		if (one_philo_die(table) == TRUE)
			break ;
		if (table->meal_no > 0 && all_philos_eat(table) == TRUE)
		{
			pthread_mutex_lock(&table->dead_lock);
			table->dead_flag = TRUE;
			pthread_mutex_unlock(&table->dead_lock);
			break ;
		}
		usleep(1000); //1 millisecond = 1000 microsecond
	}
	return ;
}

int	all_philos_eat(t_table *table)
{
	int	i;
	
	i = -1;
	while (++i < table->no_philo)
	{
		pthread_mutex_lock(&table->meal_lock);
		if (table->philo_table[i].meal_eaten < table->meal_no)
		{
			pthread_mutex_unlock(&table->meal_lock);
			return (FALSE);
		}
		pthread_mutex_unlock(&table->meal_lock);
	}
	return (TRUE);
}

int	one_philo_die(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->no_philo)
	{
		pthread_mutex_lock(&table->meal_lock);
		if (get_current_time() - table->philo_table[i].last_meal_time 
			>= table->time_to_die)
		{
			pthread_mutex_lock(&table->dead_lock);
			table->dead_flag = TRUE;
			pthread_mutex_unlock(&table->dead_lock);
			lock_and_print_death(&table->philo_table[i]);
			pthread_mutex_unlock(&table->meal_lock);
			return (TRUE);
		}
		pthread_mutex_unlock(&table->meal_lock);
	}
	return (FALSE);
}
