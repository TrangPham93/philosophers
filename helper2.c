/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:02:26 by trpham            #+#    #+#             */
/*   Updated: 2025/06/26 16:34:01 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_usleep(long long milliseconds, t_philo *philo)
{
	long long	start;

	start = get_current_time();
	if (start == FALSE)
		return (FALSE);
	while (get_current_time() - start < milliseconds) // add equal condition
	{
		if (get_dead_flag(philo) == TRUE) // if die when sleep, exit
		{
			return (FALSE);
		}
		usleep(100); // suspend execution for 500 microseconds
	}
	return (TRUE);
}

long long	get_current_time(void)
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
	pthread_mutex_lock(&philo->table->write_lock);
	if (get_dead_flag(philo) == FALSE)
		printf("%lld %d %s\n", get_current_time()
			- philo->table->start_time, (philo)->id, msg);
	pthread_mutex_unlock(&philo->table->write_lock);
}


void	lock_and_print_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->write_lock);
	printf("%lld %d %s\n", get_current_time() - philo->table->start_time,
		(philo)->id, "died");
	pthread_mutex_unlock(&philo->table->write_lock);
}

void	destroy(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->no_philo)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&table->write_lock);
	pthread_mutex_destroy(&table->dead_lock);
	pthread_mutex_destroy(&table->meal_lock);
	return ;
}

