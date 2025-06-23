/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:32:30 by trpham            #+#    #+#             */
/*   Updated: 2025/06/23 17:25:46 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (is_even_id(philo->id) == TRUE)
	{
		thinking_routine(philo);
		ft_usleep(philo->time_to_eat);
	}
	while (philo->dead_flag == FALSE)
	{
		thinking_routine(philo);
		eating_routine(philo);
		sleeping_routine(philo);
		die(philo);
	}
	
	return (NULL);
}

void	thinking_routine(t_philo *philo)
{
	lock_and_printf(philo, "is thinking");
}

void	sleeping_routine(t_philo *philo)
{
	lock_and_printf(philo, "is sleeping");
	ft_usleep((philo)->time_to_sleep);
}

void	eating_routine(t_philo *philo)
{
	if (is_even_id(philo->id) == FALSE) // odd pick l then r, release r then l
	{
		pthread_mutex_lock(philo->l_fork);
		lock_and_printf(philo, "has taken a fork");
		pthread_mutex_lock(philo->r_fork);
		lock_and_printf(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		lock_and_printf(philo, "has taken a fork");
		pthread_mutex_lock(philo->l_fork);
		lock_and_printf(philo, "has taken a fork");
	}
	lock_and_printf(philo, "is eating");
	ft_usleep(philo->time_to_eat);
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	die(t_philo *philo)
{
	if (get_current_time() - philo->last_meal_time >= philo->time_to_die)
	{
		philo->dead_flag = TRUE;
		lock_and_printf(philo, "died");
	}
}

// void	pick_fork(t_philo *philo)
// {
// 	pthread_mutex_lock(philo->l_fork);
// 	pthread_mutex_lock(philo->r_fork);
// 	printf("[%lld] %d has taken a fork \n", get_current_time(), philo->id);
// 	printf("[%lld] %d has taken a fork \n", get_current_time(), philo->id);
// 	pthread_mutex_unlock(philo->l_fork);
// 	pthread_mutex_unlock(philo->r_fork);
	
// }

