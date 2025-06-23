/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:32:30 by trpham            #+#    #+#             */
/*   Updated: 2025/06/23 14:14:11 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	thinking_routine(philo);
	while (1)
	{
		if (philo->dead_flag == FALSE && is_even_id(philo->id) == FALSE)	
		{
			// printf("ood id %d\n", (*table)->philo_table[i].id); //db
			eating_routine(philo);
			sleeping_routine(philo);
			thinking_routine(philo);
			if (philo->time_to_sleep - philo->time_to_eat < 0)
				ft_usleep(philo->time_to_eat - philo->time_to_sleep);
		}
		else if (philo->dead_flag == FALSE && is_even_id(philo->id) == TRUE)
		{
			// printf("even id %d\n", (*table)->philo_table[i].id); //db
			sleeping_routine(philo);
			thinking_routine(philo);
			eating_routine(philo);
			if (philo->time_to_eat - philo->time_to_sleep < 0)
				ft_usleep(philo->time_to_sleep - philo->time_to_eat);
		}
		
	}
	
	return (NULL);
}

void	thinking_routine(t_philo *philo)
{

	printf("[%lld] %d is thinking \n", get_current_time(), (philo)->id);
	// ft_usleep(philo.) // always thinking if not other actions
}

void	sleeping_routine(t_philo *philo)
{

	printf("[%lld] %d is sleeping \n", get_current_time(), (philo)->id);
	ft_usleep((philo)->time_to_sleep);
}

void	eating_routine(t_philo *philo)
{

	printf("[%lld] %d has taken a fork \n", get_current_time(), (philo)->id);
	pthread_mutex_lock((philo)->l_fork);
	printf("[%lld] %d has taken a fork \n", get_current_time(), (philo)->id);
	pthread_mutex_lock((philo)->r_fork);
	printf("[%lld] %d is eating \n", get_current_time(), (philo)->id);
	
	ft_usleep((philo)->time_to_eat);
	(philo)->last_meal_time = get_current_time();
	
	pthread_mutex_unlock((philo)->l_fork);
	pthread_mutex_unlock((philo)->r_fork);

}

void	die(t_philo *philo)
{
	
	if (get_current_time() - philo->last_meal_time >= philo->time_to_die)
	{
		philo->dead_flag = TRUE;
		printf("[%lld] %d died \n", get_current_time(), philo->id);
	}
}

void	pick_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(philo->r_fork);
	printf("[%lld] %d has taken a fork \n", get_current_time(), philo->id);
	printf("[%lld] %d has taken a fork \n", get_current_time(), philo->id);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	
}