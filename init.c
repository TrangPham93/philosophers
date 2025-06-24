/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 17:04:22 by trpham            #+#    #+#             */
/*   Updated: 2025/06/24 16:31:20 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_table *table)
{
	int	i;
	t_philo	*philo;
	
	i = 0;
	while (i < table->no_philo)
	{
		philo = &(table->philo_table[i]);
		philo->id = i + 1;
		philo->time_to_die = table->time_to_die;
		philo->time_to_eat = table->time_to_eat;
		philo->time_to_sleep = table->time_to_sleep;
		philo->meal_no = 0;
		philo->start_time = get_current_time();
		philo->last_meal_time = get_current_time();
		philo->dead_flag = &table->dead_flag;
		philo->l_fork = &table->forks[i];
		if (philo->id == table->no_philo)
			philo->r_fork = &table->forks[0];
		else
			philo->r_fork = &table->forks[i + 1];
		pthread_mutex_init(&philo->meal_lock, NULL);
		philo->write_lock = &table->write_lock;
		philo->dead_lock = &table->dead_lock;
		i++;
	}
}

void	init_table(t_table *table)
{
	int	i;

	i = 0;
	table->no_philo = 0;
	table->time_to_die = 0;
	table->time_to_eat = 0;
	table->time_to_sleep = 0;
	table->meal_no = 0;
	table->dead_flag = FALSE;
	memset(table->philo_table, 0, sizeof(table->philo_table));
	memset(table->forks, 0, sizeof(table->forks));
	pthread_mutex_init(&table->write_lock, NULL);
	pthread_mutex_init(&table->dead_lock, NULL);
}

void	init_forks(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->no_philo)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	} // move to after have no_philo
}