/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:54:27 by trpham            #+#    #+#             */
/*   Updated: 2025/06/21 15:41:02 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_error(char *s)
{
	printf("Error :");
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

void	init_philo(t_philo *philo)
{
	memset(philo, 0, sizeof(t_philo));
	
	
}

void	init_table(t_table **table)
{
	(*table)->size = 0;
	(*table)->time_to_die = 0;
	(*table)->time_to_eat = 0;
	(*table)->time_to_sleep = 0;
	(*table)->meal_no = 0;
	memset((*table)->philo_table, 0, sizeof(t_table));
}


