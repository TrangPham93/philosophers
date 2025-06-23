/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:02:26 by trpham            #+#    #+#             */
/*   Updated: 2025/06/23 17:42:25 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_usleep(long long milliseconds)
{
	long long	start;
	
	start = get_current_time();
	if (start == FALSE)
		return (FALSE);
	while (get_current_time() - start < milliseconds)
	{
		usleep(500); // suspend execution for 500 microseconds
	}
	return (TRUE);
}

long long get_current_time(void)
{
	struct timeval	time;
	
	if (gettimeofday(&time, NULL) != TRUE)
	{
		print_error("Gettimeofday failed");
		return (FALSE);
	}
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	lock_and_printf(t_philo *philo, char *msg)
{
	pthread_mutex_lock(philo->write_lock);
	// check if philo is alive ? no need, still print dead msg
	printf("%lld	%d %s \n", get_current_time() - philo->start_time, (philo)->id, msg);
	pthread_mutex_unlock(philo->write_lock);
}

void	destroy(t_table **table)
{
	int	i;

	i = 0;
	while (i < (*table)->size)
	{
		pthread_mutex_destroy(&(*table)->forks[i]);	
		i++;
	}
	pthread_mutex_destroy(&(*table)->write_lock);
}
