/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:54:27 by trpham            #+#    #+#             */
/*   Updated: 2025/06/21 17:30:49 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_error(char *s)
{
	printf("Error: ");
	if (!s)
		printf("Unknown\n");
	printf("%s\n", s);
}

void	free_array_null(char ***array)
{
	size_t	i;

	i = 0;
	if (!array || !*array)
		return ;
	while ((*array)[i])
	{
		free((*array)[i]);
		(*array)[i] = NULL;
		i++;
	}
	free(*array);
	*array = NULL;
}

int	array_size(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		i++;
	}
	return (i);
}

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

