/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:31:02 by trpham            #+#    #+#             */
/*   Updated: 2025/06/26 16:19:32 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	monitor_routine(t_table *table)
{
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
		usleep(500); //1 millisecond = 1000 microsecond
	}
	return (FALSE);
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
	int			i;
	long long	since_last_meal;

	i = -1;
	while (++i < table->no_philo)
	{
		pthread_mutex_lock(&table->meal_lock);
		since_last_meal = get_current_time()
			- table->philo_table[i].last_meal_time;
		pthread_mutex_unlock(&table->meal_lock);
		if (since_last_meal >= table->time_to_die) // need = ?
		{
			pthread_mutex_lock(&table->dead_lock);
			table->dead_flag = TRUE;
			pthread_mutex_unlock(&table->dead_lock);
			usleep(1000); //db
			

			// if (table->philo_table[i].is_holding_left_f == TRUE)
			// 	pthread_mutex_unlock(table->philo_table[i].l_fork);
			// if (table->philo_table[i].is_holding_right_f == TRUE)
			// 	pthread_mutex_unlock(table->philo_table[i].r_fork); //db

			lock_and_print_death(&table->philo_table[i]); //db
			return (TRUE);
		}
	}
	return (FALSE);
}
