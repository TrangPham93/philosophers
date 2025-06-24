/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:32:30 by trpham            #+#    #+#             */
/*   Updated: 2025/06/24 17:31:23 by trpham           ###   ########.fr       */
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
		if (ft_usleep(philo->time_to_eat, philo) == FALSE)
			return (NULL);
	}
	while (get_dead_flag(philo) == FALSE)
	{
		thinking_routine(philo);
		if (get_dead_flag(philo) == TRUE)
			return (NULL);
		eating_routine(philo);
		if (get_dead_flag(philo) == TRUE)
			return (NULL);
		sleeping_routine(philo);
		if (get_dead_flag(philo) == TRUE)
			return (NULL);
	}
	return (NULL);
}

void	thinking_routine(t_philo *philo)
{
	if (get_dead_flag(philo) == TRUE)
		return ;
	lock_and_printf(philo, "is thinking");
}

void	sleeping_routine(t_philo *philo)
{
	if (get_dead_flag(philo) == TRUE)
		return ;
	lock_and_printf(philo, "is sleeping");
	ft_usleep(philo->time_to_sleep, philo);
}

void	eating_routine(t_philo *philo)
{
	if (get_dead_flag(philo) == TRUE)
		return ;
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
	if (get_dead_flag(philo) == TRUE)
		return ;
	lock_and_printf(philo, "is eating");
	ft_usleep(philo->time_to_eat, philo);
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&philo->meal_lock);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

int	get_dead_flag(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*(philo->dead_flag) == TRUE)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (TRUE);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (FALSE);
}