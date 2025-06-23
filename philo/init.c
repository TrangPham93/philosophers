/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 17:04:22 by trpham            #+#    #+#             */
/*   Updated: 2025/06/23 17:46:27 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo(t_table **table)
{
	int	i;
	t_philo	*philo;
	
	i = 0;
	while (i < (*table)->size)
	{
		philo = &((*table)->philo_table[i]);
		philo->id = i + 1;
		philo->start_time = (*table)->start_time;
		philo->time_to_die = (*table)->time_to_die;
		philo->time_to_eat = (*table)->time_to_eat;
		philo->time_to_sleep = (*table)->time_to_sleep;
		philo->meal_no = (*table)->meal_no;
		philo->last_meal_time = get_current_time();
		philo->dead_flag = FALSE;
		philo->l_fork = &(*table)->forks[i];
		if (philo->id == (*table)->size)
			philo->r_fork = &(*table)->forks[0];
		else
			philo->r_fork = &(*table)->forks[i + 1];
		// philo.r_fork = malloc(sizeof(pthread_mutex_t));
		// philo.l_fork = malloc(sizeof(pthread_mutex_t));
		// if (!philo.r_fork || !philo.l_fork)
		// 	return (FALSE);
		pthread_mutex_init(philo->l_fork, NULL);
		// pthread_mutex_init(philo->r_fork, NULL);
		philo->write_lock = &(*table)->write_lock;
		i++;
	}
	return (TRUE);
}

void	init_table(t_table **table)
{
	(*table)->size = 0;
	(*table)->time_to_die = 0;
	(*table)->time_to_eat = 0;
	(*table)->time_to_sleep = 0;
	(*table)->meal_no = 0;
	(*table)->start_time = get_current_time();
	memset((*table)->philo_table, 0, sizeof((*table)->philo_table));
	memset((*table)->forks, 0, sizeof((*table)->forks));
	pthread_mutex_init(&(*table)->write_lock, NULL);
	
	
}
