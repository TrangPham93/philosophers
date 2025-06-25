/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_delete.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 15:05:44 by trpham            #+#    #+#             */
/*   Updated: 2025/06/25 11:54:56 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_array(char **arr)
{
	int	i;

	i = 0;
	printf("ARR: ");
	while (arr[i])
	{
		printf("%s, ", arr[i]);
		i++;
	}
	printf("\n");
}

void	print_long_array(long long *arr)
{
	int	i;

	i = 0;
	printf("ARR: ");
	while (arr[i])
	{
		printf("%lld, ", arr[i]);
		i++;
	}
	printf("\n");
}

// Modified lock_and_printf to accept format string and value:
void lock_and_print_msg(t_philo *philo, const char *format, int val)
{
	pthread_mutex_lock(philo->write_lock);
	printf("philo [%d] %s [%d]\n", philo->id , format, val);
	pthread_mutex_unlock(philo->write_lock);
}
