/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 21:40:27 by trpham            #+#    #+#             */
/*   Updated: 2025/06/25 22:16:51 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_left_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	lock_and_printf(philo, "has taken left fork");
}

void	lock_right_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	lock_and_printf(philo, "has taken right fork");
}

void	unlock_fork(t_philo *philo)
{
	if (is_even_id(philo->id) == FALSE)
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
}
