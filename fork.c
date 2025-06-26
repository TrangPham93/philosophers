/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 21:40:27 by trpham            #+#    #+#             */
/*   Updated: 2025/06/26 18:00:29 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	odd_lock_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	lock_and_printf(philo, "has taken left fork");
	if (get_dead_flag(philo) == TRUE)
	{
		pthread_mutex_unlock(philo->l_fork);
		return (FALSE);
	}
	pthread_mutex_lock(philo->r_fork);
	lock_and_printf(philo, "has taken right fork");
	if (get_dead_flag(philo) == TRUE)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return (FALSE);
	}
	return (TRUE);
}

int	even_lock_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	lock_and_printf(philo, "has taken right fork");
	if (get_dead_flag(philo) == TRUE)
	{
		pthread_mutex_unlock(philo->r_fork);
		return (FALSE);
	}
	pthread_mutex_lock(philo->l_fork);
	lock_and_printf(philo, "has taken left fork");
	if (get_dead_flag(philo) == TRUE)
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		return (FALSE);
	}
	return (TRUE);
}

void	unlock_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}
