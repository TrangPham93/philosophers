/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 21:40:27 by trpham            #+#    #+#             */
/*   Updated: 2025/06/26 16:31:42 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int	odd_lock_fork(t_philo *philo)
// {
// 	pthread_mutex_lock(philo->l_fork);
// 	lock_and_printf(philo, "has taken left fork");
// 	// philo->is_holding_left_f = TRUE;
// 	if (get_dead_flag(philo) == TRUE)
// 	{
// 		// philo->is_holding_left_f = FALSE;
// 		pthread_mutex_unlock(philo->l_fork);
// 		return (FALSE);
// 	}
// 	// while (pthread_mutex_lock(philo->r_fork)!= 0)
// 	// 	ft_usleep_eating(1 , (philo));
// 	// lock_and_print_msg(philo, "pick fork left and waiit for right fork");
	
	
// 	pthread_mutex_lock(philo->r_fork);
// 	lock_and_printf(philo, "has taken right fork");
// 	// philo->is_holding_right_f = TRUE;
// 	if (get_dead_flag(philo) == TRUE)
// 	{
// 		// philo->is_holding_left_f = FALSE;
// 		// philo->is_holding_right_f = FALSE;
// 		pthread_mutex_unlock(philo->l_fork);
// 		pthread_mutex_unlock(philo->r_fork);
// 		return (FALSE);
// 	}
// 	return (TRUE);
// }

void	even_lock_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	lock_and_printf(philo, "has taken right fork");
	if (get_dead_flag(philo) == TRUE)
	{
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	pthread_mutex_lock(philo->l_fork);
	lock_and_printf(philo, "has taken left fork");
	if (get_dead_flag(philo) == TRUE)
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		return ;
	}
}

void	odd_lock_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	lock_and_printf(philo, "has taken right fork");
	if (get_dead_flag(philo) == TRUE)
	{
		pthread_mutex_unlock(philo->l_fork);
		return ;
	}
	pthread_mutex_lock(philo->r_fork);
	lock_and_printf(philo, "has taken left fork");
	if (get_dead_flag(philo) == TRUE)
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		return ;
	}
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
