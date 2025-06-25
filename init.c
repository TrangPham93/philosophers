/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 17:04:22 by trpham            #+#    #+#             */
/*   Updated: 2025/06/25 12:32:25 by trpham           ###   ########.fr       */
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
		philo->meal_no = table->meal_no;
		philo->meal_eaten = 0;
		philo->no_philo = table->no_philo;
		philo->start_time = get_current_time();
		philo->last_meal_time = get_current_time();
		philo->dead_flag = &table->dead_flag;
		philo->l_fork = &table->forks[i];
		if (philo->id == table->no_philo)
			philo->r_fork = &table->forks[0];
		else
			philo->r_fork = &table->forks[i + 1];
		philo->write_lock = &table->write_lock;
		philo->dead_lock = &table->dead_lock;
		philo->meal_lock = &table->meal_lock;
		i++;
	}
}

int	init_table(t_table *table)
{
	int	i;

	i = 0;
	table->no_philo = 0;
	table->time_to_die = 0;
	table->time_to_eat = 0;
	table->time_to_sleep = 0;
	table->meal_no = FALSE;
	table->dead_flag = FALSE;
	table->all_philos_eat = FALSE;
	memset(table->philo_table, 0, sizeof(table->philo_table));
	memset(table->forks, 0, sizeof(table->forks));
	if (pthread_mutex_init(&table->write_lock, NULL) != TRUE 
		|| pthread_mutex_init(&table->dead_lock, NULL) != TRUE
		||  pthread_mutex_init(&table->meal_lock, NULL) != TRUE)
	{
		print_error("Mutex initialization failed");
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
		if (pthread_mutex_init(&table->forks[i], NULL) != TRUE)
		{
			print_error("Mutex initialization failed");
			return (FALSE);
		}
		i++;
	} // move to after have no_philo
	return (TRUE);
}