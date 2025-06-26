/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 17:04:22 by trpham            #+#    #+#             */
/*   Updated: 2025/06/26 11:27:05 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < table->no_philo)
	{
		philo = &(table->philo_table[i]);
		philo->id = i + 1;
		philo->meal_eaten = 0;
		philo->last_meal_time = FALSE; //should it?
		philo->l_fork = &table->forks[i];
		philo->r_fork = &table->forks[(i + 1) % table->no_philo];
		// if (philo->id == table->no_philo)
		// 	philo->r_fork = &table->forks[0];
		// else
		// 	philo->r_fork = &table->forks[i + 1];
		philo->table = table;
		i++;
	}
}

int	init_table(t_table *table)
{
	// int	i;

	// i = 0;
	table->no_philo = 0;
	table->time_to_die = 0;
	table->time_to_eat = 0;
	table->time_to_sleep = 0;
	table->start_time = 0;
	table->meal_no = FALSE;
	table->dead_flag = FALSE;
	table->all_philos_eat = FALSE;
	memset(table->philo_table, 0, sizeof(table->philo_table));
	memset(table->forks, 0, sizeof(table->forks));
	if (pthread_mutex_init(&table->write_lock, NULL) != 0)
		return (FALSE);
	if (pthread_mutex_init(&table->dead_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&table->write_lock);
		return (FALSE);
	}
	if (pthread_mutex_init(&table->meal_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&table->write_lock);
		pthread_mutex_destroy(&table->dead_lock);
		return (FALSE);
	}
	return (TRUE);
}

int	init_forks(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->no_philo)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&table->forks[i]);
			pthread_mutex_destroy(&table->write_lock);
			pthread_mutex_destroy(&table->dead_lock);
			pthread_mutex_destroy(&table->meal_lock);
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}
