/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:32:30 by trpham            #+#    #+#             */
/*   Updated: 2025/06/25 18:45:41 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->table->no_philo == 1)
	{
		thinking_routine(philo);
		pthread_mutex_lock(philo->l_fork);
		lock_and_printf(philo, "has taken a fork");
		ft_usleep(philo->table->time_to_die, philo);
		pthread_mutex_unlock(philo->l_fork);
		return (NULL);
	}
	// if (is_even_id(philo->id) == TRUE) //give odd number advance
	// {
	// 	thinking_routine(philo);
	// 	ft_usleep(1, philo); // 1 mlsecond works, but not longer
	// }
	while (get_dead_flag(philo) == FALSE)
	{
		thinking_routine(philo);
		if (eating_routine(philo) == FALSE)
			break ;
		sleeping_routine(philo);
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
	ft_usleep(philo->table->time_to_sleep, philo);
}

int	eating_routine(t_philo *philo)
{
	if (is_even_id(philo->id) == FALSE) // odd pick l then r, release r then l
	{
		pthread_mutex_lock(philo->l_fork);
		lock_and_printf(philo, "has taken left fork");
		pthread_mutex_lock(philo->r_fork);
		lock_and_printf(philo, "has taken righ fork");
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		lock_and_printf(philo, "has taken righ fork");
		pthread_mutex_lock(philo->l_fork);
		lock_and_printf(philo, "has taken left fork");
	}
	lock_and_printf(philo, "is eating");
	
	pthread_mutex_lock(&philo->table->meal_lock);
	philo->last_meal_time = get_current_time(); //before sleep or after
	philo->meal_eaten++;
	pthread_mutex_unlock(&philo->table->meal_lock);
	
	if (ft_usleep(philo->table->time_to_eat, philo) == FALSE) // if die when sleeping, return
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return (FALSE);
	}
	// ft_usleep(philo->table->time_to_eat, philo);
	if (is_even_id(philo->id) == FALSE)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
	}
	return (TRUE);
}

int	get_dead_flag(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->dead_lock);
	if ((philo->table->dead_flag) == TRUE)
	{
		pthread_mutex_unlock(&philo->table->dead_lock);
		return (TRUE);
	}
	pthread_mutex_unlock(&philo->table->dead_lock);
	return (FALSE);
}
