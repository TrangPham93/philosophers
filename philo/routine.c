/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:32:30 by trpham            #+#    #+#             */
/*   Updated: 2025/06/21 17:32:43 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thinking_routine(void *arg)
{
	t_philo	*philo;
	
	philo = (t_philo *)arg;
	printf("%d is thinking \n", philo->id);
	return (NULL);
}

void	*sleeping_routine(void *arg)
{
	t_philo	*philo;
	
	philo = (t_philo *)arg;
	ft_usleep(philo->time_to_sleep);
	printf("%d is sleeping \n", philo->id);
}

void	*eating_routine(void *arg)
{
	t_philo	*philo;
	
	philo = (t_philo *)arg;
	ft_usleep(philo->time_to_eat);
	printf("%d is eating \n", philo->id);
}