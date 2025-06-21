/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 17:04:22 by trpham            #+#    #+#             */
/*   Updated: 2025/06/21 17:04:37 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo(t_table **table)
{
	int	i;
	
	i = 0;
	while (i < (*table)->size)
	{
		(*table)->philo_table[i].id = i + 1;
		(*table)->philo_table[i].time_to_die = (*table)->time_to_die;
		(*table)->philo_table[i].time_to_eat = (*table)->time_to_eat;
		(*table)->philo_table[i].time_to_sleep = (*table)->time_to_sleep;
		(*table)->philo_table[i].meal_no = (*table)->meal_no;
		if (pthread_create(&(*table)->philo_table[i].thr, NULL,
			&thinking_routine, (void *)&(*table)->philo_table[i]) != TRUE)
		{
			print_error("Failed to create thread");
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

void	init_table(t_table **table)
{
	(*table)->size = 0;
	(*table)->time_to_die = 0;
	(*table)->time_to_eat = 0;
	(*table)->time_to_sleep = 0;
	(*table)->meal_no = 0;
	memset((*table)->philo_table, 0, sizeof((*table)->philo_table));
}
