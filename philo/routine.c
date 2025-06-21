/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:32:30 by trpham            #+#    #+#             */
/*   Updated: 2025/06/21 16:42:39 by trpham           ###   ########.fr       */
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
